#include "plug_mgr.h"

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
C_PlugMgr::C_PlugMgr() {

}

C_PlugMgr::~C_PlugMgr() {
 
}

void C_PlugMgr::Run() {

}

I_Plug::T_SPI_Plug C_PlugMgr::GetPlug(std::string strName) {
	auto itor = m_Name2Plug.find(strName)
	if (itor != m_Name2Plug.end()) {
		return itor->second;
	}
	return nullptr;
}

C_PlugMgr::T_SPC_PlugMgr C_PlugMgr::GetSPC_PlugMgr() {
	auto& spI_PlugMgr = GetSPI_PlugMgr()
	auto& spC_PlugMgr = std::dynamic_pointer_cast<C_PlugMgr>(spI_PlugMgr);
	return spC_PlugMgr;
}

//////////////////////////////////////////////////////////////////////
C_PlugMgr* CreateC_PlugMgr() {
	C_PlugMgr* pC_PlugMgr = New<C_PlugMgr>();
	return pC_PlugMgr;
}

void ReleaseC_PlugMgr(I_PlugMgr* pI_PlugMgr) {
	C_PlugMgr* pC_PlugMgr = static_cast<C_PlugMgr*>(pI_PlugMgr);
	Delete(pImpC_PlugMgr);
}

C_PlugMgr::T_SPC_PlugMgr C_PlugMgr::NewC_PlugMgr() {
	auto pC_PlugMgr = CreateC_PlugMgr();
	auto spC_PlugMgr = C_PlugMgr::T_SPC_PlugMgr(pC_PlugMgr, ReleaseC_PlugMgr);
	return spC_PlugMgr;
}

C_PlugMgr::T_SPI_PlugMgr C_PlugMgr::NewI_PlugMgr() {
	auto spC_PlugMgr = C_PlugMgr::NewC_PlugMgr();
	auto spI_PlugMgr = spC_PlugMgr->GetSPI_PlugMgr();
	return spI_PlugMgr;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif