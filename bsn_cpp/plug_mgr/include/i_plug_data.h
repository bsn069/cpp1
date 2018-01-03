#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <set>
#include <vector>
#include <string>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class I_PlugData {
public:
	virtual ~I_PlugData() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End