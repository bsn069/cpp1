#pragma once

#include "i_log.h"

#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/include/define.h>

D_BsnNamespace1(log)
D_FunDef D_DllCImport I_Log::T_SPI_Log	NewLog(D_N1(load_lib)::I_Lib::T_SPI_Lib);
D_BsnNamespace1End
