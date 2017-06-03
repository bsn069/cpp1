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
	virtual char const* const Name() const = 0;
	virtual char const* const Error(int32_t const i32ErrorCode) const = 0;
};
//////////////////////////////////////////////////////////////////////
}


