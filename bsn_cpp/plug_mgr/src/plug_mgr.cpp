#include <bsn_cpp/plug_mgr/src/plug_mgr.h>
#include <bsn_cpp/plug_mgr/include/i_plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/atomic.hpp>
#include <boost/atomic.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/algorithm/string.hpp>


D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
static boost::atomic<bool> fl_bQuit(false);
static boost::lockfree::spsc_queue<std::string, boost::lockfree::capacity<1024> > fl_InputCmds;


void InputThread() {
	D_OutInfo();
	std::string strCmd;
	char cInput;

	while (!fl_bQuit) {
		// D_OutInfo1("wait input");
		strCmd.clear();
		while ((cInput = getchar()) != '\n') {
			strCmd += cInput;
		}
		// D_OutInfo2("strCmd=", strCmd);
		if (!fl_InputCmds.push(strCmd)) {
			D_OutInfo1("push fail");
		}
	}
	D_OutInfo1("leave input thread");
}
//////////////////////////////////////////////////////////////////////

C_PlugMgr::C_PlugMgr() 
	: m_u32FrameMS(1000)
	, m_updateTimer(m_ioService, boost::posix_time::millisec(1))
{
	D_OutInfo();

	C_PlugData::RegPlugData();
}

C_PlugMgr::~C_PlugMgr() {
	D_OutInfo();

}

boost::asio::io_service& C_PlugMgr::GetIOService() {
	return m_ioService;
}

void C_PlugMgr::Run() {
	D_OutInfo();

	if (!LoadAll()) {
		D_OutInfo1("LoadAll fail");
		return;
	}
	if (!AwakeAll()) {
		D_OutInfo1("AwakeAll fail");
		return;
	}
	if (!InitAll()) {
		D_OutInfo1("InitAll fail");
		return;
	}
	if (!AllInitAfter()) {
		D_OutInfo1("AllInitAfter fail");
		return;
	}

	{// start input thread
		boost::thread t(InputThread);
		t.detach();
		boost::this_thread::sleep_for(boost::chrono::seconds(1));
	}

	WaitUpdate();
	m_ioService.run();

	QuitAll();
	UnInitAll();
}

bool C_PlugMgr::LoadAll() {
	D_OutInfo();
	
	if (!LoadPlug("cmd")) { return false; };
	if (!LoadPlug("base64")) { return false; };
	if (!LoadPlug("net")) { return false; };

	return true;
}

bool C_PlugMgr::LoadPlug(std::string const& strName) {
	D_OutInfo1(strName);
	auto spC_PlugData = LoadPlugData(strName);
	if (spC_PlugData == nullptr) {
		D_OutInfo1("LoadPlugData fail");
		return false;
	}
	m_Name2PlugData.insert(std::make_pair(strName, spC_PlugData));
	return true;
}

bool C_PlugMgr::AwakeAll() {
	D_OutInfo();

 	for (auto& itor : m_Name2PlugData) {
		auto& spC_PlugData = itor.second;
		if (!spC_PlugData->Awake()) {
			return false;
		}
	}

	return true;
}

bool C_PlugMgr::InitAll() {
	D_OutInfo();
 
 	for (auto& itor : m_Name2PlugData) {
		auto& spC_PlugData = itor.second;
		if (!spC_PlugData->Init(GetSPI_PlugMgr())) {
			return false;
		}
	}

	return true;
}

bool C_PlugMgr::AllInitAfter() {
	D_OutInfo();
 
 	for (auto& itor : m_Name2PlugData) {
		auto& spC_PlugData = itor.second;
		if (!spC_PlugData->AllInitAfter()) {
			return false;
		}
	}

	return true;
}

void C_PlugMgr::QuitAll() {
	D_OutInfo();
 
 	for (auto& itor : m_Name2PlugData) {
		auto& spC_PlugData = itor.second;
		spC_PlugData->Quit();
	}
}

void C_PlugMgr::UnInitAll() {
	D_OutInfo();
 
 	for (auto& itor : m_Name2PlugData) {
		auto& spC_PlugData = itor.second;
		spC_PlugData->UnInit();
	}
}

bool C_PlugMgr::ReloadPlug(std::string const& strName) {
	D_OutInfo2("strName=", strName);
	m_waitReloadPlug = strName;
	return true;
}

bool C_PlugMgr::DoReloadPlug(std::string const& strName) {
	D_OutInfo2("strName=", strName);

	auto spC_PlugData = GetPlugData(strName);
	if (spC_PlugData == nullptr) {
		D_OutInfo1("spC_PlugData == nullptr");
		return false;
	}

	for (auto& itor : m_Name2PlugData) {
		itor.second->OnReloadPre(strName);
	}

	if (!spC_PlugData->UnLoadPlug()) {
		D_OutInfo1("UnLoadPlug fail");
		return false;
	}
	if (!spC_PlugData->UnLoadLib()) {
		D_OutInfo1("UnLoadLib fail");
		return false;
	}

	if (!spC_PlugData->LoadLib()) {
		D_OutInfo1("LoadLib fail");
		return false;
	}
	if (!spC_PlugData->LoadPlug()) {
		D_OutInfo1("LoadPlug fail");
		return false;
	}

	spC_PlugData->Awake();
	spC_PlugData->Init(GetSPC_PlugMgr());
	spC_PlugData->AllInitAfter();

	for (auto& itor : m_Name2PlugData) {
		itor.second->OnReloadPost(strName);
	}
	
	return true;
}


bool C_PlugMgr::IsQuit() {
	return fl_bQuit;
}

void C_PlugMgr::PushCmd(std::string const& strCmd) {
	D_OutInfo1(strCmd);
	if (!fl_InputCmds.push(strCmd)) {
		D_OutInfo1("push fail");
	}
}

void C_PlugMgr::ProcCmd(std::string const& strCmd) {
	// D_OutInfo1(strCmd);

	auto pCmd = GetPlug("cmd");
	if (pCmd != nullptr) {
		pCmd->ProcCmd(strCmd);
	}
}

void C_PlugMgr::Update(const boost::system::error_code& ec) {
	// D_OutInfo();

	std::string strCmd;
	while (fl_InputCmds.pop(strCmd)) {
		ProcCmd(strCmd);
	}

	if (!m_waitReloadPlug.empty()) {
		DoReloadPlug(m_waitReloadPlug);
		m_waitReloadPlug.clear();
	}
	
	for (auto& itor : m_Name2PlugData) {
		auto& spC_PlugData = itor.second;
		auto spI_Plug = spC_PlugData->GetPlug();
		spI_Plug->Update();
	}

	WaitUpdate();
}

void C_PlugMgr::Quit() {
	fl_bQuit = true;
}


void C_PlugMgr::WaitUpdate() {
	static auto s_updateFunc = boost::bind(
		&C_PlugMgr::Update
		, this
		, boost::asio::placeholders::error
	);

	if (IsQuit()) {
		D_OutInfo1("in quit");
		return;
	}

	m_updateTimer.expires_at(m_updateTimer.expires_at() + boost::posix_time::millisec(m_u32FrameMS));
	m_updateTimer.async_wait(s_updateFunc);
}



C_PlugData::T_SPC_PlugData C_PlugMgr::GetPlugData(std::string const& strName) {
	D_OutInfo2("strName=", strName);
	auto itor = m_Name2PlugData.find(strName);
	if (itor != m_Name2PlugData.end()) {
		return itor->second;
	}
	return nullptr;
}

C_PlugData::T_SPC_PlugData C_PlugMgr::LoadPlugData(std::string const& strName) {
	D_OutInfo2("strName=", strName);

	auto spC_PlugData = C_PlugData::T_SPC_PlugData(new C_PlugData(strName, GetSPI_PlugMgr()));
	if (!spC_PlugData->LoadLib()) {
		D_OutInfo1("LoadLib fail");
		return nullptr;
	}
	if (!spC_PlugData->LoadPlug()) {
		D_OutInfo1("LoadPlug fail");
		return nullptr;
	}

	return spC_PlugData;
}

I_Plug::T_SPI_Plug C_PlugMgr::GetPlug(std::string strName) {
	// D_OutInfo2("strName=", strName);
	auto itor = m_Name2PlugData.find(strName);
	if (itor != m_Name2PlugData.end()) {
		return itor->second->GetPlug();
	}

	return nullptr;
}

C_PlugMgr::T_SPC_PlugMgr C_PlugMgr::GetSPC_PlugMgr() {
	D_OutInfo();
	auto spI_PlugMgr = GetSPI_PlugMgr();
	auto spC_PlugMgr = std::dynamic_pointer_cast<C_PlugMgr>(spI_PlugMgr);
	return spC_PlugMgr;
}

//////////////////////////////////////////////////////////////////////
C_PlugMgr* CreateC_PlugMgr() {
	D_OutInfo();
	C_PlugMgr* pC_PlugMgr = New<C_PlugMgr>();
	return pC_PlugMgr;
}

void ReleaseC_PlugMgr(I_PlugMgr* pI_PlugMgr) {
	D_OutInfo();
	C_PlugMgr* pC_PlugMgr = static_cast<C_PlugMgr*>(pI_PlugMgr);
	Delete(pC_PlugMgr);
}

C_PlugMgr::T_SPC_PlugMgr C_PlugMgr::NewC_PlugMgr() {
	D_OutInfo();
	auto pC_PlugMgr = CreateC_PlugMgr();
	auto spC_PlugMgr = C_PlugMgr::T_SPC_PlugMgr(pC_PlugMgr, ReleaseC_PlugMgr);
	return spC_PlugMgr;
}

C_PlugMgr::T_SPI_PlugMgr C_PlugMgr::NewI_PlugMgr() {
	D_OutInfo();
	auto spC_PlugMgr = C_PlugMgr::NewC_PlugMgr();
	auto spI_PlugMgr = spC_PlugMgr->GetSPI_PlugMgr();
	return spI_PlugMgr;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif