#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include "./interface.h"

D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////

D_FunImp I_Interface* CreateInterface()
{
	C_Interface* imp = New<C_Interface>();
	return imp;
}


D_FunImp void ReleaseInterface(I_Interface* pInterface)
{
	C_Interface* pImp = static_cast<C_Interface*>(pInterface);
	Delete(pImp);
}


D_FunImp D_DllExport I_Interface::T_SharePtr Create()
{
	auto p = I_Interface::T_SharePtr(CreateInterface(), ReleaseInterface);
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
