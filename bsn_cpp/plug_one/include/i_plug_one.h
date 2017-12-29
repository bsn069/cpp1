#pragma once

#include <bsn_cpp/plug_mgr/include/port.h>

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_one)
//////////////////////////////////////////////////////////////////////
class I_PlugOne : public D_N1(plug_mgr)::I_Plug {
public:
	typedef std::shared_ptr<I_PlugOne> T_SPI_PlugOne;
	
public:


public:
	virtual ~I_PlugOne() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End