#include <bsn/common/include/os.h>

#ifdef _WIN32
	#include <Windows.h>
	#include <mmsystem.h>
	#include <psapi.h>
#else
	#error "unknown system"
#endif

D_BsnNamespace2(Common,OS)

D_FunImp T_wchar D_const * D_const Type2Wstr(E_OSType D_const e_OSType)
{
	switch ( e_OSType )
	{
	case EOSType_WinXP:
		{
			return L"EOSType_WinXP";
		}
		break;
	case EOSType_WinVista:
		{
			return L"EOSType_WinVista";
		}
		break;
	case EOSType_Win7:
		{
			return L"EOSType_Win7";
		}
		break;
	default:
		return L"EOSType_Unknown";
	}
	BOOST_STATIC_ASSERT(4 == EOSTypes);
}


D_FunImp T_void Memory(T_uint32& u32_Total, T_uint32& u32_Free, T_uint32& u32_Used, T_uint32& u32_Peak)
{
#ifdef _WIN32
 	MEMORYSTATUS MemoryStatus;
	MemoryStatus.dwLength = sizeof(MemoryStatus);
	GlobalMemoryStatus(&MemoryStatus);

	PROCESS_MEMORY_COUNTERS Memory;
	Memory.cb = sizeof(PROCESS_MEMORY_COUNTERS);
	GetProcessMemoryInfo(GetCurrentProcess(), &Memory, sizeof(Memory));

	u32_Total = (T_uint32)MemoryStatus.dwTotalPhys;
	u32_Free = (T_uint32)MemoryStatus.dwAvailPhys;
	u32_Used = (T_uint32)Memory.WorkingSetSize;
	u32_Peak = (T_uint32)Memory.PeakWorkingSetSize;
#else
	#error "unknown system"
#endif
}

#ifdef _WIN32
D_FunImp T_bool D_const Info(OSVERSIONINFO& osinfo)
{
	ZeroMemory(&osinfo, sizeof(osinfo));
	osinfo.dwOSVersionInfoSize = sizeof(osinfo);
	return (FALSE != GetVersionEx(&osinfo));
}
#endif

D_FunImp E_OSType D_const Type( )
{
	E_OSType eOSType = EOSType_Unknown;
#ifdef _WIN32
	OSVERSIONINFO info;
	if (  Info( info ) )
	{
		if (info.dwMajorVersion <= 5)//XP or early
		{
			eOSType = EOSType_WinXP;
		}
		else
		{
			if(info.dwMinorVersion == 0)
			{
				eOSType = EOSType_WinVista;
			}else
			{
				eOSType = EOSType_Win7;
			}
		}
	}
#else
	#error "unknown system"
#endif
	return eOSType;
}

 

D_BsnNamespace2End

