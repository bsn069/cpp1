#pragma once

#include "./../include/i_lib.h"

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////
#if defined(WIN32)
typedef HMODULE T_DLL_HANDLE;
#else
typedef void* T_DLL_HANDLE;
#endif  // OS

class C_Lib : public I_Lib
{
public:
	typedef std::shared_ptr<C_Lib> T_SPC_Lib;


public:
	virtual void* 		Func(const char* strFuncName) override;
	virtual const char* Name() override;
	virtual void 		SetLog(T_SPI_Log iLog) override
	{
		m_iLog = iLog;
	};


public:
	bool   	Open(
		const char* strLibPath
		, const char* strDebugSuffix
		, const char* strReleaseSuffix
		, uint retryCount
	);
	void	Close();
	void 	SetName(char const * const pstrName);


public:
	C_Lib();
	virtual ~C_Lib();

	
private:
	T_SPI_Log 		m_iLog;
	std::string 	m_strName;
	T_DLL_HANDLE 	m_dllHandle;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End