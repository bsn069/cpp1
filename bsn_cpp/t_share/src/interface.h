#pragma once
#include "main.h"

D_BsnNamespace1(t_share)
//////////////////////////////////////////////////////////////////////

class C_Interface : public I_Interface
{
public:
	virtual char const* const Name() const override;
	virtual char const* const Error(int32_t const i32ErrorCode) const override;

	virtual void SetLibLoader(T_SharePtrLibLoader libLoader) override {
		m_libLoader = libLoader;
	}

public:
	C_Interface();
	virtual ~C_Interface();

private:
	T_SharePtrLibLoader m_libLoader;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End