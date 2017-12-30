#include "plug_mgr.h"

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
C_PlugMgr::C_PlugMgr() 
	: m_u32FrameMS(1000)
	, m_updateTimer(m_ioService, boost::posix_time::millisec(1)) 
	, m_bQuit(false) {
	D_OutInfo();

}

C_PlugMgr::~C_PlugMgr() {
	D_OutInfo();
 
}

C_PlugMgr::T_SPI_PlugMgr C_PlugMgr::GetSPI_PlugMgr() {
	D_OutInfo();
	return shared_from_this();
}


void C_PlugMgr::Run() {
	D_OutInfo();
	Awake();
	Init();

	WaitUpdate();
	m_ioService.run();

	UnInit();
}

void C_PlugMgr::Awake() {
	D_OutInfo();
	GetPlug("one");
	GetPlug("input");
}

void C_PlugMgr::Init() {
	D_OutInfo();
 
}

void C_PlugMgr::Update(const boost::system::error_code& ec) {
	D_OutInfo();

	for (auto& itor : m_Name2PlugData) {
		auto& spC_PlugData = itor.second;
		auto spI_Plug = spC_PlugData->GetPlug();
		spI_Plug->Update();
	}

	WaitUpdate();
}

void C_PlugMgr::WaitUpdate() {
	static auto s_updateFunc = boost::bind(
		&C_PlugMgr::Update
		, this
		, boost::asio::placeholders::error
	);

	if (m_bQuit) {
		D_OutInfo1("in quit");
		return;
	}

	m_updateTimer.expires_at(m_updateTimer.expires_at() + boost::posix_time::millisec(m_u32FrameMS));
	m_updateTimer.async_wait(s_updateFunc);
}

void C_PlugMgr::UnInit() {
	D_OutInfo();

}

I_Plug::T_SPI_Plug C_PlugMgr::GetPlug(std::string strName) {
	D_OutInfo2("strName=", strName);
	auto itor = m_Name2PlugData.find(strName);
	if (itor != m_Name2PlugData.end()) {
		return itor->second->GetPlug();
	}

	D_OutInfo();
	auto spC_PlugData = C_PlugData::T_SPC_PlugData(new C_PlugData(strName));
	if (!spC_PlugData->LoadLib()) {
		return nullptr;
	}
	if (!spC_PlugData->LoadPlug()) {
		return nullptr;
	}
	D_OutInfo();
	m_Name2PlugData.insert(std::make_pair(spC_PlugData->GetName(), spC_PlugData));
	D_OutInfo();
 
	return spC_PlugData->GetPlug();
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