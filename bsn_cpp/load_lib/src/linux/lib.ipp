#include <dlfcn.h>
#include <iostream>

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////
void 
C_Lib::Close() {
	D_LogInfoF(
		m_spI_Log
		, "close lib_%p name=%s"
		, this
		, Name()
	);

	if (m_dllHandle) {
		dlclose(m_dllHandle);
		m_dllHandle = nullptr;
	}
}

bool 
C_Lib::Open(
	const char* strLibPath
	, const char* strDebugSuffix
	, const char* strReleaseSuffix
	, uint retryCount
) {
	D_LogInfoF(
		m_spI_Log
		, "lib_%p name=%s strLibPath=%s,strDebugSuffix=%s,strReleaseSuffix=%s,retryCount%u)"
		, this
		, Name()
		, strLibPath
		, strDebugSuffix
		, strReleaseSuffix
		, retryCount
	);

	if (m_dllHandle != nullptr) {
		D_LogError(m_spI_Log, "had open");
		return false;
	}

	const char* strFormat = nullptr;
	switch (retryCount) {
		case 0: {
				strFormat = "%s%s";
			}
			break;
		case 1: {
				strFormat = "%s%s.so";
			}
			break;
		case 2: {
				strFormat = "lib%s%s";
			}
			break;
		case 3: {
				strFormat = "lib%s%s.so";
			}
			break;
		case 4: {
				strFormat = "./%s%s";
			}
			break;
		case 5: {
				strFormat = "./%s%s.so";
			}
			break;
		case 6: {
				strFormat = "./lib%s%s";
			}
			break;
		case 7: {
				strFormat = "./lib%s%s.so";
			}
			break;
		default: {
				char* error = dlerror();
				if (error != nullptr) {
					D_LogErrorF(
						m_spI_Log
						, "error=%s"
						, error
					);
				}
				D_LogError(m_spI_Log, "not found");
				return false;
			}
			break;
	}

	const char* strSuffix = "";
	#ifdef _DEBUG
		strSuffix= strDebugSuffix;
	#else
		strSuffix= strReleaseSuffix;
	#endif
    char szFullName[128] = {0};
	snprintf(
		szFullName
		, sizeof(szFullName)
		, strFormat
		, strLibPath
		, strSuffix
	);
	D_LogInfoF(
		m_spI_Log
		, "FullName=%s"
		, szFullName
	);

	m_dllHandle = dlopen(szFullName, RTLD_LAZY | RTLD_GLOBAL);
	if (m_dllHandle != nullptr) {
		return true;
	}
	{
		char* error = dlerror();
		if (error != nullptr) {
			D_LogErrorF(
				m_spI_Log
				, "dlopen error=%s"
				, error
			);
		}
	}

	return this->Open(strLibPath, strDebugSuffix, strReleaseSuffix, retryCount+1);
}

void* 
C_Lib::Func(char const * strFuncName) {
	D_LogInfoF(
		m_spI_Log
		, "lib_%p name=%s strFuncName=%s"
		, this
		, Name()
		, strFuncName
	);

	if (m_dllHandle == nullptr) {
		D_LogError(m_spI_Log, "not found");
		return nullptr;
	}
	dlerror();  /* Clear any existing error */
	
	void* ret   = dlsym(m_dllHandle, strFuncName);
	char* error = dlerror();
	if (error != nullptr) {
		D_LogErrorF(
			m_spI_Log
			, "error=%s"
			, error
		);
		return nullptr;
	}
	return ret;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
