#pragma once

#include "./../include/i_lib.h"
 
#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/global/include/i_global.h>
#include <bsn_cpp/log/include/i_log.h>

#include <bsn_cpp/include/name_space.h>

#include <stdarg.h>

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////

#if defined(WIN32)
typedef HMODULE T_DLL_HANDLE;
#else
typedef void* T_DLL_HANDLE;
#endif  // OS

class C_Lib : public I_Lib {
public:
	typedef std::shared_ptr<C_Lib> T_SPC_Lib;	

public:
 	static T_SPC_Lib
		NewC_Lib();
	static T_SPI_Lib
		NewI_Lib();

public:
	virtual void* 		
		Func(const char* strFuncName) override;
	virtual const char* 
		Name() override;
	virtual D_N1(global)::I_Global* 	
		GetGlobal() override;

public:
	void 
		SetGlobal(D_N1(global)::I_Global::T_SPI_Global spI_Global);
	T_SPI_Lib
		GetSPI_Lib();

	bool   	
		Open(
			const char* strLibPath
			, const char* strDebugSuffix
			, const char* strReleaseSuffix
			, uint retryCount
		);
	void	
		Close();
	void 	
		SetName(char const * const pstrName);

public:
	C_Lib();
	virtual ~C_Lib();

private:
	D_N1(global)::I_Global::T_SPI_Global m_spI_Global;
	D_N1(log)::I_Log::T_SPI_Log m_spI_Log;

	std::string 	m_strName;
	T_DLL_HANDLE 	m_dllHandle;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End