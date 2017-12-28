#include "./plug_mgr.h"

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////

D_FunDef D_DllExport I_PlugMgr::T_SPI_PlugMgr	
NewPlugMgr() {
	return I_PlugMgr::T_SPI_PlugMgr();
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
