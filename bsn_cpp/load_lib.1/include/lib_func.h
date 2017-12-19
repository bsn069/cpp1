#pragma once

#include "i_load_lib.h"

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

D_BsnNamespace1(load_lib)
D_FunDef D_DllImport I_LoadLib::T_SPI_LoadLib	NewLoadLib();
D_BsnNamespace1End
