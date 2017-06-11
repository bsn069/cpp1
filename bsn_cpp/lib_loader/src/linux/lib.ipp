#include "./../interface.h"
#include <dlfcn.h>
#include <iostream>

D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////
C_Lib::C_Lib()
{
	m_dllHandle = nullptr;
}


C_Lib::~C_Lib()
{
	D_LogInfoFmt("lib_%p name=%s"
		, this
		, Name()
	);
	this->Close();
}

void C_Lib::Close()
{
	D_LogInfoFmt("lib_%p name=%s"
		, this
		, Name()
	);

	if (m_dllHandle) {
		dlclose(m_dllHandle);
		m_dllHandle = nullptr;
	}
	m_pLog = nullptr;
}

bool C_Lib::Open(
	const char* strLibPath
	, const char* strDebugSuffix
	, const char* strReleaseSuffix
	, uint retryCount
)
{
	D_LogInfoFmt("lib_%p name=%s strLibPath=%s,strDebugSuffix=%s,strReleaseSuffix=%s,retryCount%u)"
		, this
		, Name()
		, strLibPath
		, strDebugSuffix
		, strReleaseSuffix
		, retryCount
	);

	if (m_dllHandle != nullptr)
	{
		D_LogError("had open");
		return false;
	}

	const char* strFormat = nullptr;
	switch (retryCount) 	
	{
		case 0: //
			{
				strFormat = "%s%s";
			}
			break;
		case 1: //
			{
				strFormat = "%s%s.so";
			}
			break;
		case 2: //
			{
				strFormat = "lib%s%s";
			}
			break;
		case 3: //
			{
				strFormat = "lib%s%s.so";
			}
			break;
		case 4: //
			{
				strFormat = "./%s%s";
			}
			break;
		case 5: //
			{
				strFormat = "./%s%s.so";
			}
			break;
		case 6: //
			{
				strFormat = "./lib%s%s";
			}
			break;
		case 7: //
			{
				strFormat = "./lib%s%s.so";
			}
			break;
		default:
			{
				char* error = dlerror();
				if (error != nullptr) 
				{
					D_LogErrorFmt("%s", error);
				}
				D_LogError("not found");
				return false;
			}
	}

	const char* strSuffix = "";
	#ifdef _DEBUG
		strSuffix= strDebugSuffix;
	#else
		strSuffix= strReleaseSuffix;
	#endif
    char szFullName[128] = {0};
	snprintf(szFullName, sizeof(szFullName), strFormat, strLibPath, strSuffix);
	D_LogInfoFmt("szFullName=%s", szFullName);

	m_dllHandle = dlopen(szFullName, RTLD_LAZY | RTLD_GLOBAL);
	if (m_dllHandle != nullptr) 
	{
		return true;
	}

	return this->Open(strLibPath, strDebugSuffix, strReleaseSuffix, retryCount+1);
}

void* C_Lib::Func(const char* strFuncName)
{
	D_LogInfoFmt("lib_%p name=%s strFuncName=%s"
		, this
		, Name()
		, strFuncName
	);

	void* ret = nullptr;

	if (m_dllHandle == nullptr) 
	{
		D_LogError("not found)");
		return nullptr;
	}
	dlerror();  /* Clear any existing error */
	
	ret   = dlsym(m_dllHandle, strFuncName);
	char* error = dlerror();
	if (error != nullptr) 
	{
		D_LogErrorFmt("%s", error);
		return nullptr;
	}
	return ret;
}

const char* C_Lib::Name( )
{
	return m_strName.c_str();
}


void 	C_Lib::SetName(char const * const pstrName) {
	m_strName = pstrName;
	D_LogInfoFmt("lib_%p Name=%s"
		, this
		, Name()
	);
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
