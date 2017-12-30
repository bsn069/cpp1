#include "plug_mgr.h"

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

// D_DllCImport I_Plug::T_SPI_Plug CreatePlug();
// D_DllCImport bool DestroyPlug(I_Plug::T_SPI_Plug);

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
C_PlugMgr::C_PlugMgr() {
	D_OutInfo();

}

C_PlugMgr::~C_PlugMgr() {
	D_OutInfo();
 
}

C_PlugMgr::T_SPI_PlugMgr C_PlugMgr::GetSPI_PlugMgr() {
	D_OutInfo();
	return shared_from_this();
}


void C_PlugMgr::Run() {
	D_OutInfo();
}

void C_PlugMgr::Awake() {
	D_OutInfo();
 
}

void C_PlugMgr::Init() {
	D_OutInfo();
 
}

void C_PlugMgr::Update() {
	D_OutInfo();

}

void C_PlugMgr::UnInit() {
	D_OutInfo();

}

I_Plug::T_SPI_Plug C_PlugMgr::GetPlug(std::string strName) {
	D_OutInfo2("strName=", strName);
	auto itor = m_Name2PlugData.find(strName);
	if (itor != m_Name2PlugData.end()) {
		return itor->second.GetPlug();
	}

	C_PlugData plugData(strName);
	if (!plugData.LoadLib()) {
		return nullptr;
	}
	if (!plugData.LoadPlug()) {
		return nullptr;
	}
	m_Name2PlugData.insert(std::make_pair(plugData.GetName(), plugData));
 
	return plugData.GetPlug();
}

C_PlugMgr::T_SPC_PlugMgr C_PlugMgr::GetSPC_PlugMgr() {
	D_OutInfo();
	auto spI_PlugMgr = GetSPI_PlugMgr();
	auto spC_PlugMgr = std::dynamic_pointer_cast<C_PlugMgr>(spI_PlugMgr);
	return spC_PlugMgr;
}

//////////////////////////////////////////////////////////////////////
C_PlugMgr* CreateC_PlugMgr() {
	D_OutInfo();
	C_PlugMgr* pC_PlugMgr = New<C_PlugMgr>();
	return pC_PlugMgr;
}

void ReleaseC_PlugMgr(I_PlugMgr* pI_PlugMgr) {
	D_OutInfo();
	C_PlugMgr* pC_PlugMgr = static_cast<C_PlugMgr*>(pI_PlugMgr);
	Delete(pC_PlugMgr);
}

C_PlugMgr::T_SPC_PlugMgr C_PlugMgr::NewC_PlugMgr() {
	D_OutInfo();
	auto pC_PlugMgr = CreateC_PlugMgr();
	auto spC_PlugMgr = C_PlugMgr::T_SPC_PlugMgr(pC_PlugMgr, ReleaseC_PlugMgr);
	return spC_PlugMgr;
}

C_PlugMgr::T_SPI_PlugMgr C_PlugMgr::NewI_PlugMgr() {
	D_OutInfo();
	auto spC_PlugMgr = C_PlugMgr::NewC_PlugMgr();
	auto spI_PlugMgr = spC_PlugMgr->GetSPI_PlugMgr();
	return spI_PlugMgr;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif