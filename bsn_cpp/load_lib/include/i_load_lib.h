#pragma once

#include "i_lib.h"

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/log/include/i_log.h>

#include <stdint.h>
#include <memory>
 
D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////
class I_LoadLib
{
public:
	typedef std::shared_ptr<I_LoadLib> 	T_SPI_LoadLib;
	typedef D_N1(log)::I_Log::T_SPI_Log 	T_SPI_Log;
	typedef I_Lib::T_SPI_Lib 	T_SPI_Lib;

public:
	virtual T_SPI_Lib	
		Load(
			const char* strLibName
			, const char* strLibPath
			, const char* strDebugSuffix
			, const char* strReleaseSuffix
		) = 0;
	virtual T_SPI_Lib	
		Get(const char* strLibName) = 0;
	virtual void 		
		SetLog(T_SPI_Log iLog) = 0;
	virtual void		
		WaitQuit() = 0;

protected:
	virtual ~I_LoadLib() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


