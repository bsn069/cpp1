#pragma once

#include "i_net.h"

#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/include/define.h>

D_BsnNamespace1(net)
D_FunDef D_DllCImport I_Net::T_SPI_Net	Create(D_N1(load_lib)::I_Lib::T_SPI_Lib, D_N1(common)::T_SPI_Common);
D_BsnNamespace1End
