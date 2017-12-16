#include "global.h"

#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/log/include/i_log.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(global)
//////////////////////////////////////////////////////////////////////

D_DllCExport I_Global::T_SPI_Global 
NewGlobal() {
	return C_Global::NewI_Global();
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
