#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_net.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>


D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
C_PlugDataNet::C_PlugDataNet()  {
	D_OutInfo();
}

C_PlugDataNet::~C_PlugDataNet() {
	D_OutInfo();
}

I_PlugData* C_PlugDataNet::CreateI_PlugData() {
	return New<C_PlugDataNet>();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif