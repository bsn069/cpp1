#include <bsn_cpp/plug_node/src/plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
C_Plug::C_Plug(void* pData) {
	D_OutInfo();
}

C_Plug::~C_Plug() {
	D_OutInfo();
 
}

char const * const C_Plug::GetName() const {
	return "node";
}

bool C_Plug::OnLoad(std::set<std::string>& needPlugNames) {
	D_OutInfo();

	needPlugNames.insert("net");
	needPlugNames.insert("cmd");
	return true;
}

bool C_Plug::Quit() {
	D_OutInfo();

	for (auto& pairValue : m_Id2Node) {
		auto& spC_Node = pairValue.second;
		spC_Node->Stop();
		spC_Node = nullptr;
	}
	m_Id2Node.clear();

	return I_PlugNode::Quit();
}

bool C_Plug::UnInit() {
	D_OutInfo();

	m_spI_PlugMgr = nullptr;
	return I_PlugNode::UnInit();
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
D_BsnNamespace1End
 