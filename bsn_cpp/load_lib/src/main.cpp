#include "./load_lib.h"

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////

D_FunImp I_LoadLib* CreateILoadLib()
{
	C_LoadLib* imp = New<C_LoadLib>();
	return imp;
}


D_FunImp void ReleaseILoadLib(I_LoadLib* iLoadLib)
{
	C_LoadLib* pImp = static_cast<C_LoadLib*>(iLoadLib);
	Delete(pImp);
}


D_FunImp D_DllExport I_LoadLib::T_SPI_LoadLib Create()
{
	auto p = I_LoadLib::T_SPI_LoadLib(CreateILoadLib(), ReleaseILoadLib);
	return p;
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
