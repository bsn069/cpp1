#include <bsn_cpp/plug_gate/src/gate.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_gate)
//////////////////////////////////////////////////////////////////////
C_Gate::C_Gate(C_Gate::T_SPC_Plug spC_Plug) : m_spC_Plug(spC_Plug) {
	D_OutInfo();
}

C_Gate::~C_Gate() {
	D_OutInfo();
}

C_Gate::T_SPC_Gate C_Gate::GetSPC_Gate() {
	D_OutInfo();
    return shared_from_this();
}

//////////////////////////////////////////////////////////////////////
C_Gate* CreateC_Gate(C_Gate::T_SPC_Plug spC_Plug) {
	D_OutInfo();
	C_Gate* pC_Gate = New<C_Gate>(spC_Plug);
	return pC_Gate;
}

void ReleaseC_Gate(C_Gate* pC_Gate) {
	D_OutInfo();
	Delete(pC_Gate);
}

C_Gate::T_SPC_Gate C_Gate::NewC_Gate(C_Gate::T_SPC_Plug spC_Plug) {
	D_OutInfo();
	auto pC_Gate = CreateC_Gate(spC_Plug);
	auto spC_Gate = C_Gate::T_SPC_Gate(pC_Gate, ReleaseC_Gate);
	return spC_Gate;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
