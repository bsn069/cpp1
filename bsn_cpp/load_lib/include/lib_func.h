#pragma once

#include "i_load_lib.h"

#include <bsn_cpp/global/include/i_global.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/name_space.h>

D_BsnNamespace1(load_lib)
D_FunDef D_DllImport I_LoadLib::T_SPI_LoadLib	
NewLoadLib(
	D_N1(global)::I_Global::T_SPI_Global 
);
D_BsnNamespace1End
