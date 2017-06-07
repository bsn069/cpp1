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
	this->Close();
}

void C_Lib::Close()
{
	if (m_dllHandle) {
		dlclose(m_dllHandle);
		m_dllHandle = nullptr;
	}
}

bool C_Lib::Open(
	const char* strLibPath
	, const char* strDebugSuffix
	, const char* strReleaseSuffix
	, uint retryCount
)
{
	if (m_pLog)
	{
		m_pLog->InfoFmt("C_Lib::Open(%s,%s,%s,%u)"
			, strLibPath
			, strDebugSuffix
			, strReleaseSuffix
			, retryCount
		);
	}

	if (m_dllHandle != nullptr)
	{
		if (m_pLog)
		{
			m_pLog->Error("had open");
		}
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
					if (m_pLog)
					{
						m_pLog->Error(error);
					}
				}
				if (m_pLog)
				{
					m_pLog->Error("not found");
				}
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
	if (m_pLog)
	{
		m_pLog->InfoFmt("szFullName=%s", szFullName);
	}

	m_dllHandle = dlopen(szFullName, RTLD_LAZY | RTLD_GLOBAL);
	if (m_dllHandle != nullptr) 
	{
		return true;
	}

	return this->Open(strLibPath, strDebugSuffix, strReleaseSuffix, retryCount+1);
}

void* C_Lib::Func(const char* strFuncName)
{
	if (m_pLog)
	{
		m_pLog->InfoFmt("C_Lib::Func(%s)"
			, strFuncName
		);
	}

	void* ret = nullptr;

	if (m_dllHandle == nullptr) 
	{
		if (m_pLog)
		{
			m_pLog->Error("not found)");
		}
		return nullptr;
	}
	dlerror();  /* Clear any existing error */
	
	ret   = dlsym(m_dllHandle, strFuncName);
	char* error = dlerror();
	if (error != nullptr) 
	{
		if (m_pLog)
		{
			m_pLog->Error(error);
		}
		return nullptr;
	}
	return ret;
}

const char* C_Lib::Name( )
{
	return "C_Lib::Name";
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
