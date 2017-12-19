#pragma once

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/log/include/i_log.h>

#include <memory>
 
D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////
class I_Lib
{
public:
	typedef std::shared_ptr<I_Lib> T_SPI_Lib;
	typedef D_N1(log)::I_Log::T_SPI_Log 	T_SPI_Log;

public:
	virtual void* 		
		Func(const char* strFuncName) = 0;
	virtual const char* 
		Name() = 0;
	virtual void 		
		SetLog(T_SPI_Log iLog) = 0;

protected:
	virtual ~I_Lib() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
