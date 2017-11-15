#include "./../load_lib.h"

#include <bsn_cpp/log/include/i_log_ex.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////
C_LoadLib::C_LoadLib()
{	
	D_LogInfo(m_iLog, "");
}


C_LoadLib::~C_LoadLib()
{
	D_LogInfo(m_iLog, "");
}


I_Lib::T_SPI_Lib	C_LoadLib::Load(
	const char* strLibName
	, const char* strLibPath
	, const char* strDebugSuffix
	, const char* strReleaseSuffix
)
{
	D_LogInfoF(m_iLog, "strLibName=%s,strLibPath=%s,strDebugSuffix=%s,strReleaseSuffix=%s"
		, strLibName
		, strLibPath
		, strDebugSuffix
		, strReleaseSuffix
	);

	auto pLib = std::shared_ptr<C_Lib>(New<C_Lib>(), [](C_Lib* pLib){Delete(pLib);});
	pLib->SetLog(m_iLog);
	pLib->SetName(strLibName);
	auto bLoadSuccess = pLib->Open(strLibPath, strDebugSuffix, strReleaseSuffix, 0);
	if (!bLoadSuccess)
	{
		D_LogError(m_iLog, "!bLoadSuccess")
		return nullptr;
	}

	auto pOldLib = this->Get(strLibName);
	if (pOldLib && pOldLib.use_count() > 1)
	{
		D_LogWarn(m_iLog, "pOldLib using, wait del");
		m_WaitDelLibs.push_back(pOldLib);
	}

	m_Libs[strLibName] = pLib;
	D_LogInfoF(m_iLog, "%p"
		, pLib.get()
	);
	return pLib;
}

I_Lib::T_SPI_Lib	C_LoadLib::Get(const char* strLibName)
{
	D_LogInfoF(
		m_iLog
		, "strLibName=%s"
		, strLibName
	);

	auto itor = m_Libs.find(strLibName);
	if (itor == m_Libs.end())
	{
		D_LogWarn(m_iLog, "not found");
		return nullptr;
	}
	return std::dynamic_pointer_cast<I_Lib>(itor->second);
}


void	C_LoadLib::WaitQuit() 
{
	D_LogInfoF(
		m_iLog
		, "m_Libs.size()=%u"
		, m_Libs.size()
	);

	for (auto pair : m_Libs)
	{
		auto pCLib = std::dynamic_pointer_cast<C_Lib>(pair.second);
		pCLib->SetLog(nullptr);

		m_WaitDelLibs.push_back(pair.second);
	}
	m_Libs.clear();

	D_LogInfo(m_iLog, "SetLog(nullptr)");
	SetLog(nullptr);

	auto itor = m_WaitDelLibs.begin();
	for (; itor != m_WaitDelLibs.end(); )
	{
		while ((*itor).use_count() > 1)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		++itor;
		m_WaitDelLibs.pop_front();
	}
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
