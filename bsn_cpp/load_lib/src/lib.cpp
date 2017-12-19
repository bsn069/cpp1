#include "lib.h"

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include <bsn_cpp/include/name_space.h>

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////
C_Lib::C_Lib() 
	: m_spI_Global(nullptr)
	, m_spI_Log(nullptr)
{

}

C_Lib::~C_Lib() {
	Close();

	m_spI_Log 		= nullptr;
	m_spI_Global 	= nullptr;
}

void 
C_Lib::SetGlobal(D_N1(global)::I_Global::T_SPI_Global spI_Global) {
	m_spI_Global 	= spI_Global;
	m_spI_Log		= m_spI_Global->GetLog();
}

D_N1(global)::I_Global*
C_Lib::GetGlobal() {
	return m_spI_Global.get();
}

C_Lib::T_SPI_Lib
C_Lib::GetSPI_Lib() {
	return shared_from_this();
}

char const * 
C_Lib::Name( ) {
	return m_strName.c_str();
}

void 	
C_Lib::SetName(char const * const pstrName) {
	m_strName = pstrName;
	D_LogInfoF(
		m_spI_Log
		, "lib_%p Name=%s"
		, this
		, Name()
	);
};
//////////////////////////////////////////////////////////////////////
C_Lib* 
CreateCLib() {
	C_Lib* imp = New<C_Lib>();
	return imp;
}

void 
ReleaseCLib(I_Lib* iLib) {
	C_Lib* pImp = static_cast<C_Lib*>(iLib);
	Delete(pImp);
}

C_Lib::T_SPC_Lib
C_Lib::NewC_Lib() {
	auto spC_Lib = C_Lib::T_SPC_Lib(
		CreateCLib()
		, ReleaseCLib
	);
	return spC_Lib;
}

C_Lib::T_SPI_Lib
C_Lib::NewI_Lib() {
	auto spC_Lib = C_Lib::NewC_Lib();
	return spC_Lib->GetSPI_Lib();
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
	#include "linux/lib.ipp"
#endif
