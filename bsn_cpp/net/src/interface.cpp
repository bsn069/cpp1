#include "interface.h"
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
D_FunImp void ReleaseCNet(C_Net* pCNet)
{
	Delete(pCNet); 
}

C_Interface::T_SharePtrINet C_Interface::Create() 
{
	auto pSelfC = T_SharePtrCNet(New<C_Net>(), ReleaseCNet);
	D_LogInfoFmt("p=%s", pSelfC.get());
	pSelfC->SetLog(m_pLog);
	auto pSelfI = std::dynamic_pointer_cast<I_Net>(pSelfC);
	return pSelfI;
}

void C_Interface::Release(T_SharePtrINet pINet) 
{
	auto pSelfC = std::dynamic_pointer_cast<C_Net>(pINet);
	D_LogInfoFmt("p=%s", pSelfC.get());
}

char const* const C_Interface::Error(int32_t const i32ErrorCode) const
{
	switch (i32ErrorCode)
	{
		case 1: return "1";
		default: return "Unknown";
	}
}


char const* const C_Interface::Name() const
{
	return "net";
}


C_Interface::C_Interface()
: m_lib(nullptr)
{
	D_LogInfoFmt("Name()=%s", this->Name());
}


C_Interface::~C_Interface()
{
	D_LogInfoFmt("Name()=%s", this->Name());
	SetLib(nullptr);
}

void C_Interface::SetLib(T_SharePtrLib lib) {
	m_lib = lib;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
	#include "linux/interface.ipp"
#endif