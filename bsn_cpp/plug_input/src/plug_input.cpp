#include "plug_input.h"
 
#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_input)
//////////////////////////////////////////////////////////////////////
C_PlugInput::C_PlugInput() {

}

C_PlugInput::~C_PlugInput() {
 
}

void C_PlugInput::Awake() {

}

void C_PlugInput::Init(T_SPI_PlugMgr spI_PlugMgr) {
	m_spI_PlugMgr = spI_PlugMgr;
}

void C_PlugInput::Update() {
	D_OutInfo();
}

void C_PlugInput::UnInit() {
	m_spI_PlugMgr = nullptr;
}

C_PlugInput::T_SPC_PlugInput C_PlugInput::GetSPC_PlugInput() {
	D_OutInfo();
	auto spI_Plug = GetSPI_Plug();
	auto spC_PlugInput = std::dynamic_pointer_cast<C_PlugInput>(spI_Plug);
	return spC_PlugInput;
}

//////////////////////////////////////////////////////////////////////
C_PlugInput* CreateC_PlugInput() {
	D_OutInfo();
	C_PlugInput* pC_PlugInput = New<C_PlugInput>();
	return pC_PlugInput;
}

void ReleaseC_PlugInput(I_PlugInput* pI_PlugInput) {
	D_OutInfo();
	C_PlugInput* pC_PlugInput = static_cast<C_PlugInput*>(pI_PlugInput);
	Delete(pC_PlugInput);
}

C_PlugInput::T_SPC_PlugInput C_PlugInput::NewC_PlugInput() {
	D_OutInfo();
	auto pC_PlugInput = CreateC_PlugInput();
	auto spC_PlugInput = C_PlugInput::T_SPC_PlugInput(pC_PlugInput, ReleaseC_PlugInput);
	return spC_PlugInput;
}

C_PlugInput::T_SPI_PlugInput C_PlugInput::NewI_PlugInput() {
	D_OutInfo();
	auto spC_PlugInput = C_PlugInput::NewC_PlugInput();
	auto spI_PlugInput = spC_PlugInput->GetSPI_PlugInput();
	return spI_PlugInput;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif