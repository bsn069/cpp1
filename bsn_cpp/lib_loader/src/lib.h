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
	typedef D_N1(log)::I_Log::T_SharePtr T_SharePtrLog;


public:
	virtual void* 	Func(const char* strFuncName) override;
	virtual const char* Name( ) override;


public:
	bool   	Open(
		const char* strLibPath
		, const char* strDebugSuffix
		, const char* strReleaseSuffix
		, uint retryCount
	);
	void	Close();
	void 	SetLog(T_SharePtrLog pLog) {
		m_pLog = pLog;
	};
	void 	SetName(char const * const pstrName);


public:
	C_Lib();
	virtual ~C_Lib();

private:
	T_DLL_HANDLE m_dllHandle;
	T_SharePtrLog m_pLog;
	std::string m_strName;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End