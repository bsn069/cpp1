#pragma once
#include <stdint.h>

namespace N_Bsn
{
//////////////////////////////////////////////////////////////////////

class I_LibInterface
{
public:


protected:
	virtual ~I_LibInterface() {};


public:
	virtual wchar_t const* const Name() const = 0;
	virtual wchar_t const* const Error(int32_t const i32ErrorCode) const = 0;
};
//////////////////////////////////////////////////////////////////////
}


