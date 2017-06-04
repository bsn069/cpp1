#include "./interface.h"
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(log)
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


D_FunImp D_DllCExport I_Interface::T_SharePtr Create(I_Interface::T_SharePtrLibLoader libLoader)
{
	auto p = I_Interface::T_SharePtr(CreateInterface(), ReleaseInterface);
	p->SetLibLoader(libLoader);
	return p;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
