#include "./log.h"

#include <bsn_cpp/load_lib/include/i_lib.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////

D_FunImp C_Log* CreateCLog()
{
	C_Log* imp = New<C_Log>();
	return imp;
}


D_FunImp void ReleaseILog(I_Log* iLog)
{
	C_Log* pImp = static_cast<C_Log*>(iLog);
	Delete(pImp);
}


D_FunImp D_DllExport I_Log::T_SPI_Log Create(D_N1(load_lib)::I_Lib::T_SPI_Lib iLib)
{
	auto p = C_Log::T_SPC_Log(CreateCLog(), ReleaseILog);
	p->SetLib(iLib);
	
	auto pSelfC = std::dynamic_pointer_cast<I_Log>(p);
	return pSelfC;
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
