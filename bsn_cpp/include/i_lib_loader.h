#pragma once

#include "name_space.h"
#include "define.h"
#include "i_lib.h"
#include "i_log.h"
#include "i_lib_interface.h"


#include <stdint.h>
#include <memory>
 
class I_LibLoader
{
public:
	typedef std::shared_ptr<I_LibLoader> 	T_SPI_LibLoader;
	typedef I_Log::T_SPI_Log 	T_SPI_Log;
	typedef I_Lib::T_SPI_Lib	T_SPI_Lib;

public:
	virtual T_SPI_Lib	Load(
		const char* strLibName
		, const char* strLibPath
		, const char* strDebugSuffix
		, const char* strReleaseSuffix
	) = 0;
	virtual T_SPI_Lib	Get(const char* strLibName) = 0;
	virtual void 		SetLog(T_SPI_Log iLog) = 0;
};
typedef D_FunDef I_LibLoader::T_SPI_LibLoader	(*T_FuncCreate)();
 


