#pragma once

#include "i_log.h"


#define D_LogInfoF(iLog, strFormat, ...) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		I_Log::E_Level::Info \
		, strFormat \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
		, ##__VA_ARGS__ \
	); \
} 


#define D_LogInfo(iLog, strLog) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		I_Log::E_Level::Info \
		, strLog \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
	); \
} 

#define D_LogDebugF(iLog, strFormat, ...) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		I_Log::E_Level::Debug \
		, strFormat \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
		, ##__VA_ARGS__ \
	); \
} 


#define D_LogDebug(iLog, strLog) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		I_Log::E_Level::Debug \
		, strLog \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
	); \
} 

#define D_LogWarnF(iLog, strFormat, ...) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		I_Log::E_Level::Warn \
		, strFormat \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
		, ##__VA_ARGS__ \
	); \
} 


#define D_LogWarn(iLog, strLog) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		I_Log::E_Level::Warn \
		, strLog \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
	); \
} 

#define D_LogErrorF(iLog, strFormat, ...) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		I_Log::E_Level::Error \
		, strFormat \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
		, ##__VA_ARGS__ \
	); \
} 


#define D_LogError(iLog, strLog) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		I_Log::E_Level::Error \
		, strLog \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
	); \
} 