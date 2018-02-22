#include <bsn_cpp/plug_node/src/node.h>
#include <bsn_cpp/plug_node/src/plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_node)
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
