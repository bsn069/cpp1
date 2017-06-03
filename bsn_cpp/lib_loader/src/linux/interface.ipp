#include "./../interface.h"
#include <dlfcn.h>
#include <iostream>

D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////

char const* const C_Interface::Error(int32_t const i32ErrorCode) const
{
	switch (i32ErrorCode)
	{
		case 1: return "1";
		default: return "Unknown";
	}
}


char const* const C_Interface::Name() const
{
	return "lib_loader";
}


C_Interface::C_Interface()
{
	std::cout << this->Name() << " C_Interface::C_Interface()" << std::endl;

	m_dllHandle = nullptr;
}


C_Interface::~C_Interface()
{
	std::cout << this->Name() << " C_Interface::~C_Interface()" << std::endl;
	this->Close();
}

void C_Interface::Close()
{
	if (m_dllHandle) {
		dlclose(m_dllHandle);
		m_dllHandle = nullptr;
	}
}

bool C_Interface::Open(
	const char* strLib
	, const char* strDebugSuffix
	, const char* strReleaseSuffix
	, uint retryCount
)
{
	std::cout << " strLib=" << strLib;
	std::cout << " strDebugSuffix=" << strDebugSuffix;
	std::cout << " strReleaseSuffix=" << strReleaseSuffix;
	std::cout << " retryCount=" << retryCount << std::endl;

	if (retryCount == 0)
	{
		this->Close();
	}

	const char* strFormat = nullptr;
	switch (retryCount) 	
	{
		case 0: // 当前目录
			{
				strFormat = "./lib%s%s.so";
			}
			break;
		case 1: // export LD_LIBRARY_PATH="/media/sf_/github/cpp1/bsn_cpp/out"
			{
				strFormat = "lib%s%s.so";
			}
			break;
		default:
			{
				char* error = dlerror();
				if (error != nullptr) 
				{
					std::cout << error << std::endl;
				}
				std::cout << strLib << " not found" << std::endl;
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
	snprintf(szFullName, sizeof(szFullName), strFormat, strLib, strSuffix);
	std::cout << " szFullName=" << szFullName << std::endl;

	m_dllHandle = dlopen(szFullName, RTLD_LAZY | RTLD_GLOBAL);
	if (m_dllHandle != nullptr) 
	{
		return true;
	}

	// OutputFmtToConsole("file:%s,dlopen: %s\n", strLib, dlerror());
	return this->Open(strLib, strDebugSuffix, strReleaseSuffix, retryCount+1);
}

void* C_Interface::Func(const char* strFuncName)
{
	void* ret = nullptr;

	if (m_dllHandle == nullptr) 
	{
		// OutputFmtToConsole("get func %s but handle is nullptr\n", strFuncName);
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

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
