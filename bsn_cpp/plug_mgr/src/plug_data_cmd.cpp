#include "./../include/plug_data_cmd.h"

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>


D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
C_PlugDataCmd::C_PlugDataCmd()  {
	D_OutInfo();
}

C_PlugDataCmd::~C_PlugDataCmd() {
	D_OutInfo();
}

I_PlugData* C_PlugDataCmd::CreateI_PlugData() {
	return New<C_PlugDataCmd>();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif