#include "./interface.h"
D_BsnNamespace1(DynamicLib)
//////////////////////////////////////////////////////////////////////

T_wchar D_const * D_const C_Interface::Error(T_int32 D_const i32ErrorCode) D_const
{
	switch (i32ErrorCode)
	{
		case 1: return L"had load";
		case 2: return L"load fail";
		case 3: return L"not load";
		case 4: return L"free fail";
		case 5: return L"not set name";
		case 6: return L"had load";
		case 7: return L"param is null";
		default: return L"Unknown";
	}
}


T_wchar D_const * D_const  C_Interface::Name() D_const
{
	return L"C_Imp";
}


C_Interface::C_Interface()
	: m_Lib( T_nullptr )
	, m_pLog( T_nullptr )
{

}


C_Interface::~C_Interface()
{

}



T_int32 D_const
C_Interface::Load()
{
	if (IsLoad())
	{
		return 1;
	}
	if (m_wstrLibName.empty())
	{
		return 5;
	}

	m_Lib = LoadLibraryW(m_wstrLibName.c_str());
	if (T_nullptr == m_Lib)
	{
		return 2;
	}

	return 0;
}


T_int32 D_const
C_Interface::Free()
{
	if (!IsLoad())
	{
		return 3;
	}

	BOOL bRet = FreeLibrary(m_Lib);
	if (TRUE != bRet)
	{
		return 4;
	}
	m_Lib = T_nullptr;

	return 0;
}


wstring D_const&
C_Interface::LibName() D_const
{
	return m_wstrName;
}


T_int32 D_const
C_Interface::SetName(T_wchar D_const * D_const pwcLibName)
{
	if (T_nullptr == pwcLibName)
	{
		return 7;
	}
	if (IsLoad())
	{
		return 6;
	}
	m_wstrName = pwcLibName;

	m_wstrLibName = m_wstrName;
#ifdef _DEBUG
	m_wstrLibName += L"_d";
#endif

#ifdef _WIN32
	m_wstrLibName += L".dll";
#else
	m_wstrLibName += L".so";
#endif

	return 0;
}


 


T_bool D_const
C_Interface::IsLoad() D_const
{
	return (T_nullptr != m_Lib);
}


wstring D_const&
C_Interface::LibFileName() D_const
{
	return m_wstrLibName;
}


T_void*
C_Interface::GetFunc(T_wchar D_const * D_const pwcFuncName)
{
	string strOut;
	D_N2(Common, String)::Unicode2ANSI(pwcFuncName, strOut);
	T_void* funcAddr = (T_void*)GetProcAddress(m_Lib, strOut.c_str());
	return funcAddr;
}


T_int32 D_const
C_Interface::SetLog(T_Log* pLog) 
{
	m_pLog = pLog;
	return 0;
}


I_Interface::T_Log*
C_Interface::Log()
{
	return m_pLog;
}



//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
