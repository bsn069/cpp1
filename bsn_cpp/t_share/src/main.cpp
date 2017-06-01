#include "./interface.h"


D_BsnNamespace1(NameSpace)
//////////////////////////////////////////////////////////////////////

D_FunImp D_BSN_template_share_lib_DLL I_Interface* Create()
{
	C_Interface* imp = New<C_Interface>();
	return imp;
}


D_FunImp D_BSN_template_share_lib_DLL T_void Release(I_Interface* pInterface)
{
	C_Interface* pImp = static_cast<C_Interface*>(pInterface);
	Delete(pImp);
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
