#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug_data.h>
#include <bsn_cpp/plug_mgr/include/i_plug_mgr.h>

#include <bsn_cpp/include/name_space.h>

#include <set>
#include <vector>
#include <string>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class C_PlugDataCmd : public I_PlugData {
public:
	std::set<std::string> m_Plugs;
	std::string m_strCurPlug;
	std::vector<std::string> m_PlugStack;
	
public:
	C_PlugDataCmd();
	virtual ~C_PlugDataCmd();

	static I_PlugData* CreateI_PlugData(I_PlugMgr::T_SPI_PlugMgr);
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End