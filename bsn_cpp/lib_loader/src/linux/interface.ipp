#include "./../interface.h"
#include <dlfcn.h>

D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////

wchar_t const* const C_Interface::Error(int32_t const i32ErrorCode) const
{
	switch (i32ErrorCode)
	{
		case 1: return L"1";
		default: return L"Unknown";
	}
}


wchar_t const* const C_Interface::Name() const
{
	return L"lib_loader";
}


C_Interface::C_Interface()
{
	m_dllHandle = nullptr;
}


C_Interface::~C_Interface()
{
	this->Close();
}

void C_Interface::Close()
{
	if (m_dllHandle) {
		dlclose(m_dllHandle);
		m_dllHandle = nullptr;
	}
}

bool C_Interface::Open(const char* strLib)
{
	this->Close();

	m_dllHandle = dlopen(strLib, RTLD_LAZY | RTLD_GLOBAL);
	if (m_dllHandle == nullptr) 
	{
		// OutputFmtToConsole("file:%s,dlopen: %s\n", strLib, dlerror());
		return false;
	}
	return true;
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
		// OutputFmtToConsole("get_func[%s], error:%s\n", strFuncName, error);
		return nullptr;
	}
	return ret;
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
