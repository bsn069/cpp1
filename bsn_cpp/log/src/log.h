#pragma once

#include "./../include/i_log.h"
 
#include <bsn_cpp/load_lib/include/i_lib.h>

#include <stdarg.h>

D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////
class C_Log : public I_Log 
{
public:
	typedef std::shared_ptr<C_Log> T_SPC_Log;	
	typedef D_N1(load_lib)::I_Lib::T_SPI_Lib T_SPI_Lib;

public:
	virtual void Push(
		E_Level eLevel
		, char const * strFile
		, uint32_t u32Line
		, char const * strFunc
		, char const * strLog
	) override;

	virtual void PushF(
		E_Level eLevel
		, char const * strFile
		, uint32_t u32Line
		, char const * strFunc
		, char const * strLog
		, ...
	) override;

	virtual void 
		Init() override;
	virtual void 
		Start() override;
	virtual void 
		Quit() override;
	virtual void		
		UnInit() override;

public:
	void SetLib(T_SPI_Lib spI_Lib) {
		m_spI_Lib = spI_Lib;
	};
	void FmtPrint(
			I_Log::E_Level eLevel
			, char const * strFile
			, uint32_t u32Line
			, char const * strFunc
			,const char * strFormat
			, va_list args
		);
	void Print(
			I_Log::E_Level eLevel
			, char const * strFile
			, uint32_t u32Line
			, char const * strFunc
			, char const * strInfo
		);
	void UpdateTime();

public:
	C_Log();
	virtual ~C_Log();

private:
	T_SPI_Lib m_spI_Lib;
	char m_pszTime[128];
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End