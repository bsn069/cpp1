#pragma once
#include <stdint.h>
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

#include <memory>

D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////
class I_Lib
{
public:
	typedef std::shared_ptr<I_Lib> T_SharePtr;

public:
	virtual void* 		Func(const char* strFuncName) = 0;
	virtual const char* Name() = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


