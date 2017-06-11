#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include "./interface.h"


D_BsnNamespace1(console_input)
//////////////////////////////////////////////////////////////////////

D_FunImp C_Interface* CreateInterface()
{
	C_Interface* imp = New<C_Interface>();
	return imp;
}


D_FunImp void ReleaseInterface(I_Interface* pInterface)
{
	C_Interface* pImp = static_cast<C_Interface*>(pInterface);
	Delete(pImp);
}


D_FunImp D_DllCExport I_Interface::T_SharePtr Create(I_Interface::T_SharePtrLib lib)
{
	auto p = C_Interface::T_CSharePtr(CreateInterface(), ReleaseInterface);
	p->SetLib(lib);
	
	auto pSelfC = std::dynamic_pointer_cast<I_Interface>(p);
	return pSelfC;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
