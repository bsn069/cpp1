#include "./../include/plug_data_log.h"

#include <bsn_cpp/include/d_out.h>


D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
C_PlugDataLog::C_PlugDataLog()  {
	D_OutInfo();
}

C_PlugDataLog::~C_PlugDataLog() {
	D_OutInfo();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif