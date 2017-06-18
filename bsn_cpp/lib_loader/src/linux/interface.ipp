#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include "./../interface.h"
#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////

char const* const C_Interface::Error(int32_t const i32ErrorCode) const
{
	switch (i32ErrorCode)
	{
		case 1: return "1";
		default: return "Unknown";
	}
}


char const* const C_Interface::Name() const
{
	return "lib_loader";
}


C_Interface::C_Interface()
{	
	D_LogInfo("");
}


C_Interface::~C_Interface()
{
	D_LogInfo("");
}


I_Lib::T_SharePtr	C_Interface::Load(
	const char* strLibName
	, const char* strLibPath
	, const char* strDebugSuffix
	, const char* strReleaseSuffix
)
{
	D_LogInfoFmt("strLibName=%s,strLibPath=%s,strDebugSuffix=%s,strReleaseSuffix=%s"
		, strLibName
		, strLibPath
		, strDebugSuffix
		, strReleaseSuffix
	);

	auto pLib = std::shared_ptr<C_Lib>(New<C_Lib>(), [](C_Lib* pLib){Delete(pLib);});
	pLib->SetLog(m_pLog);
	pLib->SetName(strLibName);
	auto bLoadSuccess = pLib->Open(strLibPath, strDebugSuffix, strReleaseSuffix, 0);
	if (!bLoadSuccess)
	{
		D_LogError("!bLoadSuccess")
		return nullptr;
	}

	auto pOldLib = this->Get(strLibName);
	if (pOldLib && pOldLib.use_count() > 1)
	{
		D_LogWarn("pOldLib using, wait del");
		m_WaitDelLibs.push_back(pOldLib);
	}

	m_Libs[strLibName] = pLib;
	D_LogInfoFmt("%p"
		, pLib.get()
	);
	return pLib;
}

I_Lib::T_SharePtr	C_Interface::Get(const char* strLibName)
{
	D_LogInfoFmt("strLibName=%s"
		, strLibName
	);

	auto itor = m_Libs.find(strLibName);
	if (itor == m_Libs.end())
	{
		D_LogWarn("not found");
		return nullptr;
	}
	return std::dynamic_pointer_cast<I_Lib>(itor->second);
}


void	C_Interface::WaitQuit() 
{
	D_LogInfoFmt("m_Libs.size()=%u"
		, m_Libs.size()
	);

	for (auto pair : m_Libs)
	{
		auto pCLib = std::dynamic_pointer_cast<C_Lib>(pair.second);
		pCLib->SetLog(nullptr);

		m_WaitDelLibs.push_back(pair.second);
	}
	m_Libs.clear();

	D_LogInfo("SetLog(nullptr)");
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
