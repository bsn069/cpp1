#pragma once
#include <stdint.h>
#include <bsn_cpp/include/name_space.h>
D_BsnNamespace1(NameSpace)
//////////////////////////////////////////////////////////////////////

class I_Interface
{
public:


protected:
	virtual ~I_Interface() {};


public:
	virtual wchar_t const* const Name() const = 0;
	virtual wchar_t const* const Error(int32_t const i32ErrorCode) const = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


