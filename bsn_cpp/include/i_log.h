#pragma once

#include <stdint.h>
#include <memory>
#include <iostream>
 
class I_Log 
{
public:
	typedef std::shared_ptr<I_Log> T_SPI_Log;
	enum E_Level
	{
		Debug 	= 1 << 0,
		Info 	= 1 << 1,
		Warn 	= 1 << 2,
		Error 	= 1 << 3,
	};
	
public:
	virtual void Push(
		E_Level eLevel
		, char const * strLog
		, char const * strFile
		, uint32_t u32Line
		, char const * strFunc
	) = 0;

	virtual void PushF(
		E_Level eLevel
		, char const * strLog
		, char const * strFile
		, uint32_t u32Line
		, char const * strFunc
		, ...
	) = 0;
};
 