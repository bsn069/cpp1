#include "./../interface.h"
#include <dlfcn.h>
#include <iostream>

D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////
C_Lib::C_Lib()
{
	std::cout << this->Name() << " C_Lib::C_Lib()" << std::endl;
	m_dllHandle = nullptr;
}


C_Lib::~C_Lib()
{
	std::cout << this->Name() << " C_Lib::~C_Lib()" << std::endl;
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
	std::cout << " strLibPath=" << strLibPath;
	std::cout << " strDebugSuffix=" << strDebugSuffix;
	std::cout << " strReleaseSuffix=" << strReleaseSuffix;
	std::cout << " retryCount=" << retryCount << std::endl;

	if (m_dllHandle != nullptr)
	{
		std::cout << strLibPath << " had open" << std::endl;
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
					std::cout << error << std::endl;
				}
				std::cout << strLibPath << " not found" << std::endl;
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
	std::cout << " szFullName=" << szFullName << std::endl;

	m_dllHandle = dlopen(szFullName, RTLD_LAZY | RTLD_GLOBAL);
	if (m_dllHandle != nullptr) 
	{
		return true;
	}

	// OutputFmtToConsole("file:%s,dlopen: %s\n", strLib, dlerror());
	return this->Open(strLibPath, strDebugSuffix, strReleaseSuffix, retryCount+1);
}

void* C_Lib::Func(const char* strFuncName)
{
	void* ret = nullptr;

	if (m_dllHandle == nullptr) 
	{
		// OutputFmtToConsole("get func %s but handle is nullptr\n", strFuncName);
		std::cout << " lib not open" << std::endl;
		return nullptr;
	}
	dlerror();  /* Clear any existing error */
	
	ret   = dlsym(m_dllHandle, strFuncName);
	char* error = dlerror();
	if (error != nullptr) 
	{
		std::cout << strFuncName << " error= " <<  error << std::endl;
		// OutputFmtToConsole("get_func[%s], error:%s\n", strFuncName, error);
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
