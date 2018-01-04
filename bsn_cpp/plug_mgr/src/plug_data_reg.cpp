#include "plug_data.h"

#include "./../include/plug_data_cmd.h"
#include "./../include/plug_data_log.h"
#include "./../include/plug_data_net.h"

#include <bsn_cpp/include/new.hpp>


D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////

#define D_RegPlugData(strPlugName, className) \
	m_Name2FuncCreatePlugData[#strPlugName] = className::CreateI_PlugData

bool C_PlugData::RegPlugData() {
	//m_Name2FuncCreatePlugData["cmd"] = C_PlugDataCmd::CreateI_PlugData;
	D_RegPlugData(cmd, C_PlugDataCmd);
	return true;
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif