#include <bsn_cpp/plug_mgr/include/lib_func.h>
#include <bsn_cpp/plug_mgr/include/i_plug_mgr.h>
#include <bsn_cpp/plug_mgr/src/plug_mgr.h>

#include <bsn_cpp/include/name_space.h>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
D_BSN_plug_mgr_DLL I_PlugMgr::T_SPI_PlugMgr NewPlugMgr() {
	return C_PlugMgr::NewI_PlugMgr();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
