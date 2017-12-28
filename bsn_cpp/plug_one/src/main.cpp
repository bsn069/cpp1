#include "./plug_one.h"

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_one)
//////////////////////////////////////////////////////////////////////

D_FunDef D_DllExport I_PlugOne::T_SPI_PlugOne	
NewPlugOne() {
 
	
	return I_PlugOne::T_SPI_PlugOne();
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
