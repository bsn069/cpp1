#include "./../include/plug_data_net.h"

#include <bsn_cpp/include/d_out.h>


D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
C_PlugDataNet::C_PlugDataNet()  {
	D_OutInfo();
}

C_PlugDataNet::~C_PlugDataNet() {
	D_OutInfo();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif