#pragma once
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

#include <stdint.h>
#include <memory>

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
			strFormat " file:%s line:%d func:%s" \
			, ##__VA_ARGS__ \
			, __FILE__ \
			, __LINE__ \
			, __FUNCTION__ \
		); \
	}


#define D_LogWarnFmt(strFormat, ...) \
	if (m_pLog) \
	{ \
		m_pLog->WarnFmt( \
			strFormat " file:%s line:%d func:%s" \
			, ##__VA_ARGS__ \
			, __FILE__ \
			, __LINE__ \
			, __FUNCTION__ \
		); \
	}


#define D_LogErrorFmt(strFormat, ...) \
	if (m_pLog) \
	{ \
		m_pLog->ErrorFmt( \
			strFormat " file:%s line:%d func:%s" \
			, ##__VA_ARGS__ \
			, __FILE__ \
			, __LINE__ \
			, __FUNCTION__ \
		); \
	}


#define D_LogInfo(strInfo) \
	if (m_pLog) \
	{ \
		m_pLog->InfoFmt( \
			strInfo " file:%s line:%d func:%s" \
			, __FILE__ \
			, __LINE__ \
			, __FUNCTION__ \
		); \
	}


#define D_LogWarn(strInfo) \
	if (m_pLog) \
	{ \
		m_pLog->WarnFmt( \
			strInfo " file:%s line:%d func:%s" \
			, __FILE__ \
			, __LINE__ \
			, __FUNCTION__ \
		); \
	}


#define D_LogError(strInfo) \
	if (m_pLog) \
	{ \
		m_pLog->ErrorFmt( \
			strInfo " file:%s line:%d func:%s" \
			, __FILE__ \
			, __LINE__ \
			, __FUNCTION__ \
		); \
	}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


