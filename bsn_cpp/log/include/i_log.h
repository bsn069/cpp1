#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <iostream>

D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////
class I_Log 
{
public:
	typedef std::shared_ptr<I_Log> T_SPI_Log;
	enum E_Level
	{
		Debug 	= 0,
		Info 	= 1,
		Warn 	= 2,
		Error 	= 3,
	};
	
public:
	virtual void Push(
		E_Level eLevel
		, char const * strFile
		, uint32_t u32Line
		, char const * strFunc
		, char const * strLog
	) = 0;

	virtual void PushF(
		E_Level eLevel
		, char const * strFile
		, uint32_t u32Line
		, char const * strFunc
		, char const * strLog
		, ...
	) = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End