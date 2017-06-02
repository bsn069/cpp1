#pragma once
#include "./main.h"
D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////
#if defined(WIN32)
typedef HMODULE T_DLL_HANDLE;
#else
typedef void* T_DLL_HANDLE;
#endif  // OS

class C_Interface : public I_Interface
{
public:
	virtual bool   	Open(const char* strLib) override;
	virtual void	Close() override;
	virtual void* 	Func(const char* strFuncName) override;


public:
	virtual wchar_t const* const Name() const override;
	virtual wchar_t const* const Error(int32_t const i32ErrorCode) const override;

public:
	C_Interface();
	virtual ~C_Interface();

private:
	T_DLL_HANDLE m_dllHandle;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End