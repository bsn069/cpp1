#define D_OutInfo(strLog1) \
	std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strLog1 << std::endl 

#define D_OutInfo2(strLog1, strLog2) \
	std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strLog1 << strLog2 << std::endl 

#define D_OutInfo3(strLog1, strLog2, strLog3) \
	std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strLog1 << strLog2 << strLog3 << std::endl 

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
} else { \
	std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strFormat << std::endl; \
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
} else { \
	std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strLog << std::endl; \
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
} else { \
	std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strFormat << std::endl; \
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
} else { \
	std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strLog << std::endl; \
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
} else { \
	std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strFormat << std::endl; \
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
} else { \
	std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strLog << std::endl; \
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
} else { \
	std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strFormat << std::endl; \
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
} else { \
	std::cout << __FILE__ << ":" << __LINE__ << "(" << __FUNCTION__ << ") " << strLog << std::endl; \
}
 