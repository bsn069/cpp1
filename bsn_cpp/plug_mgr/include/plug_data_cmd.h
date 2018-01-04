#pragma once

#include "i_plug_data.h"

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
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

	static I_PlugData* CreateI_PlugData();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End