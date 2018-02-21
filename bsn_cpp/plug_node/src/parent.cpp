#include <bsn_cpp/plug_node/src/node.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
C_Parent::C_Parent(C_Parent::T_SPC_Node spC_Node) : m_spC_Node(spC_Node) {
	D_OutInfo();
}

C_Parent::~C_Parent() {
	D_OutInfo();
}

C_Parent::T_SPC_Parent C_Parent::GetSPC_Parent() {
	D_OutInfo();
    return shared_from_this();
}

//////////////////////////////////////////////////////////////////////
C_Parent* CreateC_Parent(C_Parent::T_SPC_Node spC_Node) {
	D_OutInfo();
	C_Parent* pC_Parent = New<C_Parent>(spC_Node);
	return pC_Parent;
}

void ReleaseC_Parent(C_Parent* pC_Parent) {
	D_OutInfo();
	Delete(pC_Parent);
}

C_Parent::T_SPC_Parent C_Parent::NewC_Parent(C_Parent::T_SPC_Node spC_Node) {
	D_OutInfo();
	auto pC_Parent = CreateC_Parent(spC_Node);
	auto spC_Parent = C_Parent::T_SPC_Parent(pC_Parent, ReleaseC_Parent);
	return spC_Parent;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
