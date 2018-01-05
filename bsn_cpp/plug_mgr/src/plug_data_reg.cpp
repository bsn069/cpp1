#include <bsn_cpp/plug_mgr/src/plug_data.h>

#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_cmd.h>
#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_log.h>
#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_net.h>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////

#define D_RegPlugData(strPlugName, className) \
	m_Name2FuncCreatePlugData[#strPlugName] = className::CreateI_PlugData

bool C_PlugData::RegPlugData() {
	D_RegPlugData(cmd, C_PlugDataCmd);
	D_RegPlugData(net, C_PlugDataNet);
	D_RegPlugData(log, C_PlugDataLog);
	return true;
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif