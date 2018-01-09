#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_log.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>


D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
C_PlugDataLog::C_PlugDataLog()  {
	D_OutInfo();
}

C_PlugDataLog::~C_PlugDataLog() {
	D_OutInfo();
}

I_PlugData* C_PlugDataLog::CreateI_PlugData(I_PlugMgr::T_SPI_PlugMgr) {
	return New<C_PlugDataLog>();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif