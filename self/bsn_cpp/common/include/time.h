#pragma once

#include <bsn/include/port.h>
#include <bsn/common/include/lib_def.h>
D_BsnNamespace2(Common, Time)


// һ���ӵ�����
static T_uint32 D_const msc_u32Min		= 60;
// һСʱ������
static T_uint32 D_const msc_u32Hour	= 60 * msc_u32Min;
// һ�������
static T_uint32 D_const msc_u32Day		= 24 * msc_u32Hour;
// һ�ܵ�����
static T_uint32 D_const msc_u32Week	= 7 * msc_u32Day;

// ��ȡwday��Ӧ������
// [0,6]ת���й���[1,7]����
static T_uint32 D_const msc_u32WeekDayChina[] = {7,1,2,3,4,5,6};


// ��ȡ�й���tm 1�¿�ʼ ��1��ʼ
D_FunDef D_BSN_common_DLL T_void TmChina(tm& vTm);
D_FunDef D_BSN_common_DLL T_void TmChina(time_t& vTime, tm& vTm);
// ������
D_FunDef D_BSN_common_DLL T_uint32 D_const Days(T_uint32 D_const u32Time);
// ��ǰ��u32ʱ��
D_FunDef D_BSN_common_DLL T_uint32 D_const U32Time( );
// �ڵ��յ�����
D_FunDef D_BSN_common_DLL T_uint32 D_const DaySec(T_uint32 D_const u32Time);
// ���� 
// X����X+1�� ���1��
D_FunDef D_BSN_common_DLL T_uint32 D_const DiffDay(T_uint32 D_const u32Time0, T_uint32 D_const u32Time1);
/*�����¸���ʱ��������
	 *dwTimeNow static_cast<DWORD>( time(NULL) )
	 *dwWeekDay	[1,7]
	 *dwHour	[0,23]
	 *dwMin		[0,59]
	 *dwSec		[0,59]
	 */
D_FunDef D_BSN_common_DLL T_uint32 D_const DiffNextWeekSec(	
	T_uint32 D_const u32TimeNow
	, T_uint32 D_const u32WeekDay
	, T_uint32 D_const u32Hour
	, T_uint32 D_const u32Min
	, T_uint32 D_const u32Sec
	);


class D_BSN_common_DLL C_Timer
{
public:
	double D_const	NowSec( );
	
	void		SleepTo(double D_const dSec);
	void		SleepSec(double D_const dSec);


public:
	double m_dFrequency;


public:
	C_Timer();
};

 

D_BsnNamespace2End
