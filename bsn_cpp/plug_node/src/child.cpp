#include <bsn_cpp/plug_node/src/node.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
C_Child::C_Child(C_Child::T_SPC_Node spC_Node) : m_spC_Node(spC_Node) {
	D_OutInfo();
}

C_Child::~C_Child() {
	D_OutInfo();
}

C_Child::T_SPC_Child C_Child::GetSPC_Child() {
	D_OutInfo();
    return shared_from_this();
}

//////////////////////////////////////////////////////////////////////
C_Child* CreateC_Child(C_Child::T_SPC_Node spC_Node) {
	D_OutInfo();
	C_Child* pC_Child = New<C_Child>(spC_Node);
	return pC_Child;
}

void ReleaseC_Child(C_Child* pC_Child) {
	D_OutInfo();
	Delete(pC_Child);
}

C_Child::T_SPC_Child C_Child::NewC_Child(C_Child::T_SPC_Node spC_Node) {
	D_OutInfo();
	auto pC_Child = CreateC_Child(spC_Node);
	auto spC_Child = C_Child::T_SPC_Child(pC_Child, ReleaseC_Child);
	return spC_Child;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
