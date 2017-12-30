#include "plug_one.h"
 
#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_one)
//////////////////////////////////////////////////////////////////////
C_PlugOne::C_PlugOne() {

}

C_PlugOne::~C_PlugOne() {
 
}

void C_PlugOne::Awake() {

}

void C_PlugOne::Init(T_SPI_PlugMgr spI_PlugMgr) {
	m_spI_PlugMgr = spI_PlugMgr;
}

void C_PlugOne::Update() {

}

void C_PlugOne::UnInit() {
	m_spI_PlugMgr = nullptr;
}

C_PlugOne::T_SPC_PlugOne C_PlugOne::GetSPC_PlugOne() {
	D_OutInfo();
	auto spI_Plug = GetSPI_Plug();
	auto spC_PlugOne = std::dynamic_pointer_cast<C_PlugOne>(spI_Plug);
	return spC_PlugOne;
}

void C_PlugOne::ProcCmd(std::string const& strCmd) {
	D_OutInfo1(strCmd);
}

//////////////////////////////////////////////////////////////////////
C_PlugOne* CreateC_PlugOne() {
	D_OutInfo();
	C_PlugOne* pC_PlugOne = New<C_PlugOne>();
	return pC_PlugOne;
}

void ReleaseC_PlugOne(I_PlugOne* pI_PlugOne) {
	D_OutInfo();
	C_PlugOne* pC_PlugOne = static_cast<C_PlugOne*>(pI_PlugOne);
	Delete(pC_PlugOne);
}

C_PlugOne::T_SPC_PlugOne C_PlugOne::NewC_PlugOne() {
	D_OutInfo();
	auto pC_PlugOne = CreateC_PlugOne();
	auto spC_PlugOne = C_PlugOne::T_SPC_PlugOne(pC_PlugOne, ReleaseC_PlugOne);
	return spC_PlugOne;
}

C_PlugOne::T_SPI_PlugOne C_PlugOne::NewI_PlugOne() {
	D_OutInfo();
	auto spC_PlugOne = C_PlugOne::NewC_PlugOne();
	auto spI_PlugOne = spC_PlugOne->GetSPI_PlugOne();
	return spI_PlugOne;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif