#include "./interface.h"
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>


D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////

D_FunImp D_BSN_lib_loader_DLL I_Interface* Create()
{
	C_Interface* imp = New<C_Interface>();
	return imp;
}


D_FunImp D_BSN_lib_loader_DLL void Release(I_Interface* pInterface)
{
	C_Interface* pImp = static_cast<C_Interface*>(pInterface);
	Delete(pImp);
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
