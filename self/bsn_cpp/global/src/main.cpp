#include "./interface.h"


D_BsnNamespace1(Global)
//////////////////////////////////////////////////////////////////////

D_FunImp D_BSN_Global_DLL D_N1(Other)::I_Global* Create()
{
	C_Global* imp = New<C_Global>();
	return imp;
}


D_FunImp D_BSN_Global_DLL T_void Release(D_N1(Other)::I_Global* pInterface)
{
	C_Global* pImp = static_cast<C_Global*>(pInterface);
	Delete(pImp);
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
