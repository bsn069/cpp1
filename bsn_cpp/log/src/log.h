#pragma once
#include "./../include/i_log.h"
#include "./../include/i_interface.h"
#include "interface.h"
#include <stdarg.h>

D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////
class C_Log : public I_Log 
{
public:
	typedef C_Interface::T_CSharePtr T_SharePtrCInterface;

public:
	virtual void InfoFmt(const char * strFormat, ...) override;
	virtual void WarnFmt(const char * strFormat, ...) override;
	virtual void ErrorFmt(const char * strFormat, ...) override;

	virtual void Info(const char * strInfo) override;
	virtual void Warn(const char * strInfo) override;
	virtual void Error(const char * strInfo) override;

public:
	char const* Name() const;
	void FmtPrint(uint32_t uLogLevel, const char * strFormat, va_list args);

public:
	C_Log(T_SharePtrCInterface pInterface);
	virtual ~C_Log();

private:
	T_SharePtrCInterface m_pInterface;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End