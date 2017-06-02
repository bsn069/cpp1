#pragma once
#include <stdint.h>
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/i_lib_interface.h>
D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////

class I_Interface : public I_LibInterface
{
public:
	virtual void InfoFmt(const char * strFormat, ...);
	virtual void WarnFmt(const char * strFormat, ...);
	virtual void ErrorFmt(const char * strFormat, ...);

	virtual void Info(const char * strInfo);
	virtual void Warn(const char * strInfo);
	virtual void Error(const char * strInfo);
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


