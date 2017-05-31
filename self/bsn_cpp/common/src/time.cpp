#include <bsn/common/include/time.h>

#ifdef _WIN32
	#include <Windows.h>
#else
	#error "unknown system"
#endif
D_BsnNamespace2(Common,Time)
 


 


D_FunImp T_void TmChina(tm& vTm)
{
	time_t	vTime	= time( NULL );
	TmChina( vTime, vTm );
}


D_FunDef T_void TmChina(  time_t& vTime,tm& vTm)
{
	localtime_s(&vTm, &vTime);
	vTm.tm_year	+= 1900;
	vTm.tm_mon	+= 1;
	vTm.tm_wday = msc_u32WeekDayChina[ vTm.tm_wday ];
}


D_FunImp  T_uint32 D_const Days(  T_uint32 D_const u32Time)
{
	return ((u32Time - 57600) / 86400);
}


D_FunImp T_uint32 D_const U32Time()
{
	return (T_uint32)(time( NULL ));
}


D_FunImp T_uint32 D_const DaySec(  T_uint32 D_const u32Time)
{
	return ((u32Time - 57600) % 86400);
}


D_FunImp T_uint32 D_const DiffDay(  T_uint32 D_const u32Time0, T_uint32 D_const u32Time1)
{
	DWORD dwCurDay0 = Days(u32Time0);
	DWORD dwCurDay1 = Days(u32Time1);
	if (dwCurDay0 > dwCurDay1)
	{
		return (dwCurDay0 - dwCurDay1);
	}
	return (dwCurDay1 - dwCurDay0);
}


D_FunImp T_uint32 D_const DiffNextWeekSec(  T_uint32 D_const u32TimeNow , T_uint32 D_const u32WeekDay , T_uint32 D_const u32Hour , T_uint32 D_const u32Min , T_uint32 D_const u32Sec)
{
	time_t vTime = (time_t)u32TimeNow;
	tm vTm;
	TmChina(vTime, vTm);

	// ����ʱ���ڵ��������
	T_uint32 D_const u32DaySec = u32Hour * msc_u32Hour +u32Min *  msc_u32Min + u32Sec;
	// ���չ��˶�������
	T_uint32 D_const u32CurDaySec = DaySec( u32TimeNow );

	// ����������� ������dwWeekDay �� ����
	T_uint32 u32DiffDay = 6;
	T_uint32 D_const u32CurWeekDay = static_cast<T_uint32>(vTm.tm_wday);
	if (u32CurWeekDay < u32WeekDay)
	{// �ڱ��� ��δ��
		// ��4����5 ��		0��
		// ��3����5 ��4		1��
		u32DiffDay = (u32WeekDay - u32CurWeekDay) - 1;
	}
	else	if (u32CurWeekDay > u32WeekDay)
	{// ������
		// ��6����5 ��7 1234 	5��
		// ��7����5 ��0 1234	4��
		u32DiffDay = (7 - u32CurWeekDay) + (u32WeekDay - 1);
	}
	else
	{// �ڱ���
		if (u32CurDaySec < u32DaySec)
		{// ָ��ʱ��δ��
			return u32DaySec - u32CurDaySec;
		}
	}

	return (
		( msc_u32Day - u32DaySec) // ��ʣ��sec
		+  msc_u32Day * u32DiffDay // ����������sec
		+ u32DaySec // 
		);
}






D_FunImp C_Timer::C_Timer()
{
	// /��ȡÿ�����CPU Performance Tick 
	LARGE_INTEGER nFrequency = {0};
	QueryPerformanceFrequency(&nFrequency);
	m_dFrequency = (double)nFrequency.QuadPart;
}


D_FunImp double D_const C_Timer::NowSec()
{
	LARGE_INTEGER nCounts = {0};

	HANDLE hThread = GetCurrentThread(); 
	DWORD_PTR dwMask = SetThreadAffinityMask(hThread, 1); 
	QueryPerformanceCounter(&nCounts);
	SetThreadAffinityMask(hThread, dwMask);

	return (double)nCounts.QuadPart / m_dFrequency;
}


D_FunImp T_void C_Timer::SleepTo(  double D_const dSec)
{
	double D_const dNow = NowSec();
	if(dNow < dSec)
	{
		SleepSec(dSec - dNow);
	}
}


D_FunImp T_void C_Timer::SleepSec(  double D_const dSec)
{
	Sleep( static_cast<DWORD>(dSec * 1000.0) );
}

D_BsnNamespace2End

