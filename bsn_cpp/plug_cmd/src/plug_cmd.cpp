#include "plug_cmd.h"
 
#include <bsn_cpp/plug_mgr/include/i_plug_mgr.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>

D_BsnNamespace1(plug_cmd)
//////////////////////////////////////////////////////////////////////
C_PlugCmd::C_PlugCmd(void* pData) {
	D_OutInfo();
	m_pData = reinterpret_cast<T_PlugData*>(pData);
}

C_PlugCmd::~C_PlugCmd() {
	D_OutInfo();
 
}

char const * const C_PlugCmd::GetName() const {
	return "cmd";
}

bool C_PlugCmd::Awake() {
	D_OutInfo();

	return true;
}

bool C_PlugCmd::Init(T_SPI_PlugMgr spI_PlugMgr) {
	D_OutInfo();
	m_spI_PlugMgr = spI_PlugMgr;
	return true;
}

bool C_PlugCmd::AllInitAfter() {
	D_OutInfo();

	m_pData->m_strCurPlug = GetName();
	RegPlugCmd(GetName(), "quit", boost::bind(&C_PlugCmd::CmdQuit, this, _1, _2));
	RegPlugCmd(GetName(), "ls", boost::bind(&C_PlugCmd::CmdLS, this, _1, _2));
	RegPlugCmd(GetName(), "cd", boost::bind(&C_PlugCmd::CmdCD, this, _1, _2));
	RegPlugCmd(GetName(), "pwd", boost::bind(&C_PlugCmd::CmdPWD, this, _1, _2));
	return true;
}

void C_PlugCmd::CmdPWD(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);

	D_OutInfo2("cur plug:", m_pData->m_strCurPlug);
}

void C_PlugCmd::CmdCD(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);

	D_OutInfo2("leave plug:", m_pData->m_strCurPlug);
	m_pData->m_strCurPlug = strParam;
	D_OutInfo2("enter plug:", m_pData->m_strCurPlug);
}

void C_PlugCmd::CmdLS(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);

	D_OutInfo1("plug list:");
	for (auto& itor : m_PlugCmds) {
		D_OutInfo1(itor.first);
	}
}

void C_PlugCmd::CmdQuit(bool bShowHelp, std::string const& strParam) {
	D_OutInfo2(bShowHelp, strParam);

	m_spI_PlugMgr->Quit();
}

bool C_PlugCmd::Update() {
	// D_OutInfo();
	return true;
}

bool C_PlugCmd::Quit() {
	D_OutInfo();
	return true;
}

bool C_PlugCmd::UnInit() {
	D_OutInfo();
	m_spI_PlugMgr = nullptr;
	return true;
}

void C_PlugCmd::OnReloadPre(std::string const& strName) {
	D_OutInfo();
	
}

void C_PlugCmd::OnReloadPost(std::string const& strName) {
	D_OutInfo();
	
}


C_PlugCmd::T_SPC_PlugCmd C_PlugCmd::GetSPC_PlugCmd() {
	D_OutInfo();
	auto spI_Plug = GetSPI_Plug();
	auto spC_PlugCmd = std::dynamic_pointer_cast<C_PlugCmd>(spI_Plug);
	return spC_PlugCmd;
}

void C_PlugCmd::ProcCmd(std::string const& strCmd) {
	D_OutInfo1(strCmd);

	auto& cmd2Func = m_PlugCmds[m_pData->m_strCurPlug];
	auto itor = cmd2Func.find(strCmd);
	if (itor != cmd2Func.end()) {
		auto& func = itor->second;
		func(false, strCmd);
		return;
	}
	D_OutInfo1("unknown cmd");
}

void C_PlugCmd::RegPlug(std::string const& strName) {
	D_OutInfo();
	m_pData->m_Plugs.insert(strName);
}

bool C_PlugCmd::HadRegPlug(std::string const& strName) {
	D_OutInfo();
	return m_pData->m_Plugs.find(strName) != m_pData->m_Plugs.end();
}

std::string const& C_PlugCmd::GetCurPlug() {
	D_OutInfo();
	return m_pData->m_strCurPlug;
}

void C_PlugCmd::CDPlug(std::string const& strName) {
	D_OutInfo();
	m_pData->m_strCurPlug = strName;
}

void C_PlugCmd::QuitPlug(std::string const& strName) {
	D_OutInfo();
	m_pData->m_strCurPlug.clear();
}

void C_PlugCmd::RegPlugCmd(
	std::string const& strPlug
	, std::string const& strCmd
	, T_FuncCmd funcCmd
) {
	D_OutInfo2(strPlug, strCmd);
	
	auto& cmd2Func = m_PlugCmds[strPlug];
	cmd2Func[strCmd] = funcCmd;
}

//////////////////////////////////////////////////////////////////////
C_PlugCmd* CreateC_PlugCmd(void* pData) {
	D_OutInfo();
	C_PlugCmd* pC_PlugCmd = New<C_PlugCmd>(pData);
	return pC_PlugCmd;
}

void ReleaseC_PlugCmd(I_PlugCmd* pI_PlugCmd) {
	D_OutInfo();
	C_PlugCmd* pC_PlugCmd = static_cast<C_PlugCmd*>(pI_PlugCmd);
	Delete(pC_PlugCmd);
}

C_PlugCmd::T_SPC_PlugCmd C_PlugCmd::NewC_PlugCmd(void* pData) {
	D_OutInfo();
	auto pC_PlugCmd = CreateC_PlugCmd(pData);
	auto spC_PlugCmd = C_PlugCmd::T_SPC_PlugCmd(pC_PlugCmd, ReleaseC_PlugCmd);
	return spC_PlugCmd;
}

C_PlugCmd::T_SPI_PlugCmd C_PlugCmd::NewI_PlugCmd(void* pData) {
	D_OutInfo();
	auto spC_PlugCmd = C_PlugCmd::NewC_PlugCmd(pData);
	auto spI_PlugCmd = spC_PlugCmd->GetSPI_PlugCmd();
	return spI_PlugCmd;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif