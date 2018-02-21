#include <bsn_cpp/plug_gate/src/plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_gate)
//////////////////////////////////////////////////////////////////////
C_Plug::C_Plug(void* pData) {
	D_OutInfo();
}

C_Plug::~C_Plug() {
	D_OutInfo();
 
}

char const * const C_Plug::GetName() const {
	return "gate";
}

bool C_Plug::OnLoad(std::set<std::string>& needPlugNames) {
	D_OutInfo();

	needPlugNames.insert("net");
	needPlugNames.insert("cmd");
	return true;
}

bool C_Plug::InitNeedPlug() {
    D_OutInfo();

    m_spI_PlugNet = m_spI_PlugMgr->GetPlugPtr<D_N1(plug_net)::I_PlugNet>("net");
	if (!m_spI_PlugNet) {
		return false;
	}

    m_spI_PlugCmd = m_spI_PlugMgr->GetPlugPtr<D_N1(plug_cmd)::I_PlugCmd>("cmd");
	if (!m_spI_PlugCmd) {
		return false;
	}

    return true;
}

bool C_Plug::ClearNeedPlug() {
    D_OutInfo();

    m_spI_PlugNet = nullptr;
    m_spI_PlugCmd = nullptr;

    return true;
}

void C_Plug::RegPlugCmd(std::string const& strCmd, T_FuncCmd funcCmd) {
    D_OutInfo();

	GetSPI_PlugCmd()->RegPlugCmd(GetName(), strCmd, funcCmd);
}
 
C_Plug::T_SPC_Plug C_Plug::GetSPC_Plug() {
    D_OutInfo();
    auto spI_Plug = GetSPI_Plug();
    auto spC_Plug = std::dynamic_pointer_cast<C_Plug>(spI_Plug);
    return spC_Plug;
}

C_Plug::T_SPI_PlugNet C_Plug::GetSPI_PlugNet() {
    return m_spI_PlugNet;
}

C_Plug::T_SPI_PlugCmd C_Plug::GetSPI_PlugCmd() {
    return m_spI_PlugCmd;
}


//////////////////////////////////////////////////////////////////////
C_Plug* CreateC_Plug(void* pData) {
	D_OutInfo();
	C_Plug* pC_Plug = New<C_Plug>(pData);
	return pC_Plug;
}

void ReleaseC_Plug(I_Plug* pI_Plug) {
	D_OutInfo();
	C_Plug* pC_Plug = static_cast<C_Plug*>(pI_Plug);
	Delete(pC_Plug);
}

C_Plug::T_SPC_Plug C_Plug::NewC_Plug(void* pData) {
	D_OutInfo();
	auto pC_Plug = CreateC_Plug(pData);
	auto spC_Plug = C_Plug::T_SPC_Plug(pC_Plug, ReleaseC_Plug);
	return spC_Plug;
}

I_Plug::T_SPI_Plug C_Plug::NewI_Plug(void* pData) {
	D_OutInfo();
	auto spC_Plug = C_Plug::NewC_Plug(pData);
	auto spI_Plug = spC_Plug->GetSPI_Plug();
	return spI_Plug;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 