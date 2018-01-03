#include "plug_net.h"

#include <bsn_cpp/plug_mgr/include/i_plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
D_DllCExport D_N1(plug_mgr)::I_Plug::T_SPI_Plug	CreatePlug(void* pData) {
	D_OutInfo();
	return C_PlugNet::NewI_PlugNet(pData);
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
