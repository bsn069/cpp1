#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_one)
//////////////////////////////////////////////////////////////////////
class I_PlugOne : public std::enable_shared_from_this<I_PlugOne> {
public:
	typedef std::shared_ptr<I_PlugOne> T_SPI_PlugOne;
	
public:
	// virtual void
	// 	RegCmd(char const* pszCmd, ) = 0;

public:
	virtual ~I_PlugOne() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End