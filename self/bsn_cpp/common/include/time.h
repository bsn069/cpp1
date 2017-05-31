#pragma once

#include <bsn/include/port.h>
#include <bsn/common/include/lib_def.h>
D_BsnNamespace2(Common, Time)


// 一分钟的秒数
static T_uint32 D_const msc_u32Min		= 60;
// 一小时的秒数
static T_uint32 D_const msc_u32Hour	= 60 * msc_u32Min;
// 一天的秒数
static T_uint32 D_const msc_u32Day		= 24 * msc_u32Hour;
// 一周的秒数
static T_uint32 D_const msc_u32Week	= 7 * msc_u32Day;

// 获取wday对应的星期
// [0,6]转成中国周[1,7]那种
static T_uint32 D_const msc_u32WeekDayChina[] = {7,1,2,3,4,5,6};


// 获取中国的tm 1月开始 周1开始
D_FunDef D_BSN_common_DLL T_void TmChina(tm& vTm);
D_FunDef D_BSN_common_DLL T_void TmChina(time_t& vTime, tm& vTm);
// 总日数
D_FunDef D_BSN_common_DLL T_uint32 D_const Days(T_uint32 D_const u32Time);
// 当前的u32时间
D_FunDef D_BSN_common_DLL T_uint32 D_const U32Time( );
// 在当日的秒数
D_FunDef D_BSN_common_DLL T_uint32 D_const DaySec(T_uint32 D_const u32Time);
// 相差几天 
// X日与X+1日 相差1天
D_FunDef D_BSN_common_DLL T_uint32 D_const DiffDay(T_uint32 D_const u32Time0, T_uint32 D_const u32Time1);
/*距离下个周时间差多少秒
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
