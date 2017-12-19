#pragma once

#include "i_lib.h"

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////
class I_LoadLib : public std::enable_shared_from_this<I_LoadLib> {
public:
	typedef std::shared_ptr<I_LoadLib> T_SPI_LoadLib;
	
public:
	virtual I_Lib::T_SPI_Lib	
		Load(
			const char* strLibName
			, const char* strLibPath
			, const char* strDebugSuffix
			, const char* strReleaseSuffix
		) = 0;
	virtual I_Lib::T_SPI_Lib	
		Get(const char* strLibName) = 0;
	virtual void		
		UnInit() = 0;

protected:
	virtual ~I_LoadLib() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End