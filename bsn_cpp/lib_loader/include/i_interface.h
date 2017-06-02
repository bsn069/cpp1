#pragma once
#include <stdint.h>
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/i_lib_interface.h>

D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////

class I_Interface : public I_LibInterface
{
public:
	virtual bool   	Open(const char* strLib);
	virtual void	Close();
	virtual void* 	Func(const char* strFuncName);
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


