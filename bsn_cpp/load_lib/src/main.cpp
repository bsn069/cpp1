#include "load_lib.h"

#include <bsn_cpp/global/include/i_global.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <bsn_cpp/include/name_space.h>


D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////

D_FunImp D_DllExport I_LoadLib::T_SPI_LoadLib 
NewLoadLib(
	D_N1(global)::I_Global::T_SPI_Global spI_Global
) {
	auto spC_LoadLib = C_LoadLib::NewC_LoadLib();
	spC_LoadLib->SetGlobal(spI_Global);
	
	return spC_LoadLib->GetSPI_LoadLib();
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
