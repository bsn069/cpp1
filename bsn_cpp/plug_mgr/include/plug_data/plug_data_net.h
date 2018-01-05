#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug_data.h>

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <set>
#include <vector>
#include <string>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class C_PlugDataNet : public I_PlugData {
public:
 
	
public:
	C_PlugDataNet();
	virtual ~C_PlugDataNet();

	static I_PlugData* CreateI_PlugData();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End