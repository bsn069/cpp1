#pragma once
#include "main.h"


D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////

class C_Interface : public I_Interface
{
public:
	virtual char const* const Name() const override;
	virtual char const* const Error(int32_t const i32ErrorCode) const override;

	virtual void InfoFmt(const char * strFormat, ...) override;
	virtual void WarnFmt(const char * strFormat, ...) override;
	virtual void ErrorFmt(const char * strFormat, ...) override;

	virtual void Info(const char * strInfo) override;
	virtual void Warn(const char * strInfo) override;
	virtual void Error(const char * strInfo) override;

	virtual void SetLib(T_SharePtrLib lib) override {
		m_lib = lib;
	}

public:
	C_Interface();
	virtual ~C_Interface();

private:
	T_SharePtrLib m_lib;

private:
	void FmtPrint(const char * strFormat, ...);
	void Print(const char * strInfo);
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End