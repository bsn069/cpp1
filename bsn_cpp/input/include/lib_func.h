#pragma once

#include "i_input.h"

#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/name_space.h>

D_BsnNamespace1(input)
typedef I_Input::T_SPI_Input	
(*T_NewInput)(
	D_N1(load_lib)::I_Lib::T_SPI_Lib
);
D_BsnNamespace1End
