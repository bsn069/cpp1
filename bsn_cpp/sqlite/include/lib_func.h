#pragma once

#include "i_db.h"

#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/log/include/i_log.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/name_space.h>

D_BsnNamespace1(sqlite)

// D_DllCImport I_DB::T_SPI_DB 
// NewDB(
// 	D_N1(load_lib)::I_Lib::T_SPI_Lib spI_Lib
// 	, D_N1(log)::I_Log::T_SPI_Log spI_Log
// );
 
typedef I_DB::T_SPI_DB	(*T_NewDB)(
	D_N1(load_lib)::I_Lib::T_SPI_Lib spI_Lib
	, D_N1(log)::I_Log::T_SPI_Log spI_Log
);
D_BsnNamespace1End
