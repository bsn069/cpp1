#include <bsn_cpp/plug_node/src/node.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
C_Node::C_Node(C_Node::T_SPC_Plug spC_Plug, C_Node::T_SPI_Address spI_AddressListen, C_Node::T_Id id) 
    : m_spC_Plug(spC_Plug) 
    , m_spI_AddressListen(spI_AddressListen) 
    , m_id(id)
{
	D_OutInfo();
}

C_Node::~C_Node() {
	D_OutInfo();
}

C_Node::T_SPC_Node C_Node::GetSPC_Node() {
	D_OutInfo();
    return shared_from_this();
}

bool C_Node::StartTCPListen() {
	D_OutInfo();

    auto spI_PlugNet = m_spC_Plug->GetSPI_PlugNet();
    if (!spI_PlugNet) {
		return false;
	}

	m_spI_TCPListen = spI_PlugNet->NewI_TCPListen();
	m_spI_TCPListen->SetAddress(m_spI_AddressListen);
	m_spI_TCPListen->SetFuncNew(
		boost::bind(&C_Node::FuncNew, GetSPC_Node())
	);
	m_spI_TCPListen->SetFuncOnAccept(
		boost::bind(&C_Node::FuncOnAccept, GetSPC_Node(), _1)
	);
	m_spI_TCPListen->StartListen();
	
	return true;
}

C_Node::T_SPI_TCPSession C_Node::FuncNew() {
    D_OutInfo();

    auto spI_PlugNet = m_spC_Plug->GetSPI_PlugNet();
	if (!spI_PlugNet) {
		return nullptr;
	}

	auto spI_TCPSession = spI_PlugNet->NewI_TCPSession();
	return spI_TCPSession;
}

void C_Node::FuncOnAccept(C_Node::T_SPI_TCPSession spI_TCPSession) {
    D_OutInfo();
}

bool C_Node::SetParentAddr(C_Node::T_SPI_Address spI_AddressParent) {
    D_OutInfo();

    m_spI_AddressParent = spI_AddressParent;
    return true;
}

C_Node::T_Id C_Node::GetId() const {
    return m_id;
}

//////////////////////////////////////////////////////////////////////
C_Node* CreateC_Node(C_Node::T_SPC_Plug spC_Plug, C_Node::T_SPI_Address spI_AddressListen, C_Node::T_Id id) {
	D_OutInfo();
	C_Node* pC_Node = New<C_Node>(spC_Plug, spI_AddressListen, id);
	return pC_Node;
}

void ReleaseC_Node(C_Node* pC_Node) {
	D_OutInfo();
	Delete(pC_Node);
}

C_Node::T_SPC_Node C_Node::NewC_Node(C_Node::T_SPC_Plug spC_Plug, C_Node::T_SPI_Address spI_AddressListen, C_Node::T_Id id) {
	D_OutInfo();
	auto pC_Node = CreateC_Node(spC_Plug, spI_AddressListen, id);
	auto spC_Node = C_Node::T_SPC_Node(pC_Node, ReleaseC_Node);
	return spC_Node;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
