#define D_LogInfoF(iLog, strFormat, ...) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		D_N1(log)::I_Log::E_Level::Info \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
		, strFormat \
		, ##__VA_ARGS__ \
	); \
} 


#define D_LogInfo(iLog, strLog) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		D_N1(log)::I_Log::E_Level::Info \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
		, strLog \
	); \
} 

#define D_LogDebugF(iLog, strFormat, ...) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		D_N1(log)::I_Log::E_Level::Debug \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
		, strFormat \
		, ##__VA_ARGS__ \
	); \
} 


#define D_LogDebug(iLog, strLog) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		D_N1(log)::I_Log::E_Level::Debug \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
		, strLog \
	); \
} 

#define D_LogWarnF(iLog, strFormat, ...) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		D_N1(log)::I_Log::E_Level::Warn \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
		, strFormat \
		, ##__VA_ARGS__ \
	); \
} 


#define D_LogWarn(iLog, strLog) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		D_N1(log)::I_Log::E_Level::Warn \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
		, strLog \
	); \
} 

#define D_LogErrorF(iLog, strFormat, ...) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		D_N1(log)::I_Log::E_Level::Error \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
		, strFormat \
		, ##__VA_ARGS__ \
	); \
} 


#define D_LogError(iLog, strLog) \
if (iLog != nullptr) \
{ \
	iLog->PushF( \
		D_N1(log)::I_Log::E_Level::Error \
		, __FILE__ \
		, __LINE__ \
		, __FUNCTION__ \
		, strLog \
	); \
} 
 