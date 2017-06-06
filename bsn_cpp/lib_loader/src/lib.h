#pragma once
#include "./../include/i_lib.h"
D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////
#if defined(WIN32)
typedef HMODULE T_DLL_HANDLE;
#else
typedef void* T_DLL_HANDLE;
#endif  // OS

class C_Lib : public I_Lib
{
public:
	bool   	Open(
		const char* strLibPath
		, const char* strDebugSuffix
		, const char* strReleaseSuffix
		, uint retryCount
	);
	void	Close();
	virtual void* 	Func(const char* strFuncName) override;
	virtual const char* Name( ) override;

public:
	C_Lib();
	virtual ~C_Lib();

private:
	T_DLL_HANDLE m_dllHandle;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End