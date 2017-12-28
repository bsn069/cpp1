#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class I_PlugMgr : public std::enable_shared_from_this<I_PlugMgr> {
public:
	typedef std::shared_ptr<I_PlugMgr> T_SPI_PlugMgr;
	
public:
	// virtual void
	// 	RegCmd(char const* pszCmd, ) = 0;

public:
	virtual ~I_PlugMgr() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End