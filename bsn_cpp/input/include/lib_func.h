#pragma once

#include "i_input.h"

#include <bsn_cpp/global/include/i_global.h>
#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/name_space.h>

D_BsnNamespace1(input)
D_FunDef D_DllImport I_Input::T_SPI_Input
NewInput(
	D_N1(global)::I_Global::T_SPI_Global 
);
D_BsnNamespace1End
