#pragma once
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/i_lib_interface.h>
#include <bsn_cpp/include/define.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////

class I_Interface : public I_LibInterface
{
public:
	typedef std::shared_ptr<I_Interface> T_SharePtr;

	
public:
	virtual void InfoFmt(const char * strFormat, ...) = 0;
	virtual void WarnFmt(const char * strFormat, ...) = 0;
	virtual void ErrorFmt(const char * strFormat, ...) = 0;

	virtual void Info(const char * strInfo) = 0;
	virtual void Warn(const char * strInfo) = 0;
	virtual void Error(const char * strInfo) = 0;
};

typedef D_FunDef I_Interface::T_SharePtr	(*T_FuncCreate)();

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


