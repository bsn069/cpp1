#pragma once
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

#include <stdint.h>
#include <memory>
#include <iostream>

D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////
class I_Log 
{
public:
	typedef std::shared_ptr<I_Log> T_SharePtr;
	
public:
	virtual void InfoFmt(const char * strFormat, ...) = 0;
	virtual void WarnFmt(const char * strFormat, ...) = 0;
	virtual void ErrorFmt(const char * strFormat, ...) = 0;

	virtual void Info(const char * strInfo) = 0;
	virtual void Warn(const char * strInfo) = 0;
	virtual void Error(const char * strInfo) = 0;
};

#define D_LogInfoFmt(strFormat, ...) \
	if (m_pLog) \
	{ \
		m_pLog->InfoFmt( \
			strFormat " (%s:%d %s)" \
			, ##__VA_ARGS__ \
			, __FILE__ \
			, __LINE__ \
			, __FUNCTION__ \
		); \
	} \
	else \
	{\
		std::cout << "D_LogInfoFmt(" << strFormat << ") (" << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << ")" << std::endl;\
	}



#define D_LogWarnFmt(strFormat, ...) \
	if (m_pLog) \
	{ \
		m_pLog->WarnFmt( \
			strFormat " (%s:%d %s)" \
			, ##__VA_ARGS__ \
			, __FILE__ \
			, __LINE__ \
			, __FUNCTION__ \
		); \
	} \
	else \
	{\
		std::cout << "D_LogWarnFmt(" << strFormat << ") (" << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << ")" << std::endl;\
	}



#define D_LogErrorFmt(strFormat, ...) \
	if (m_pLog) \
	{ \
		m_pLog->ErrorFmt( \
			strFormat " (%s:%d %s)" \
			, ##__VA_ARGS__ \
			, __FILE__ \
			, __LINE__ \
			, __FUNCTION__ \
		); \
	} \
	else \
	{\
		std::cout << "D_LogErrorFmt(" << strFormat << ") (" << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << ")" << std::endl;\
	}



#define D_LogInfo(strInfo) \
	if (m_pLog) \
	{ \
		m_pLog->InfoFmt( \
			strInfo " (%s:%d %s)" \
			, __FILE__ \
			, __LINE__ \
			, __FUNCTION__ \
		); \
	} \
	else \
	{\
		std::cout << "D_LogInfo(" << strInfo << ") (" << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << ")" << std::endl;\
	}


#define D_LogWarn(strInfo) \
	if (m_pLog) \
	{ \
		m_pLog->WarnFmt( \
			strInfo " (%s:%d %s)" \
			, __FILE__ \
			, __LINE__ \
			, __FUNCTION__ \
		); \
	}\
	else \
	{\
		std::cout << "D_LogWarn(" << strInfo << ") (" << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << ")" << std::endl;\
	}


#define D_LogError(strInfo) \
	if (m_pLog) \
	{ \
		m_pLog->ErrorFmt( \
			strInfo " (%s:%d %s)" \
			, __FILE__ \
			, __LINE__ \
			, __FUNCTION__ \
		); \
	}\
	else \
	{\
		std::cout << "D_LogError(" << strInfo << ") (" << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << ")" << std::endl;\
	}



//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


