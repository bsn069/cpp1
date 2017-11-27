#include "./load_lib.h"

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////

D_FunImp I_Common* CreateICommon()
{
	C_Common* imp = New<C_Common>();
	return imp;
}


D_FunImp void ReleaseICommon(I_Common* iCommon)
{
	C_Common* pImp = static_cast<C_Common*>(iCommon);
	Delete(pImp);
}


D_FunImp D_DllExport I_Common::T_SPI_Common Create()
{
	auto p = I_Common::T_SPI_Common(CreateICommon(), ReleaseICommon);
	return p;
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
