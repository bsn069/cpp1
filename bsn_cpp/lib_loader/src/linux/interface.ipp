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
	std::cout << this->Name() << " C_Interface::C_Interface()" << std::endl;

}


C_Interface::~C_Interface()
{
	std::cout << this->Name() << " C_Interface::~C_Interface()" << std::endl;
	this->WaitQuit();
}

I_Lib::T_SharePtr	C_Interface::Load(
	const char* strLibName
	, const char* strLibPath
	, const char* strDebugSuffix
	, const char* strReleaseSuffix
)
{
	auto pLib = std::shared_ptr<C_Lib>(New<C_Lib>(), [](C_Lib* pLib){Delete(pLib);});
	auto bLoadSuccess = pLib->Open(strLibPath, strDebugSuffix, strReleaseSuffix, 0);
	if (!bLoadSuccess)
	{
		return nullptr;
	}

	auto pOldLib = this->Get(strLibName);
	if (pOldLib && pOldLib.use_count() > 1)
	{
		auto pTemp = std::dynamic_pointer_cast<I_Lib>(pOldLib);
		m_WaitDelLibs.push_back(pTemp);
	}

	m_Libs[strLibName] = pLib;
	return pLib;
}

I_Lib::T_SharePtr	C_Interface::Get(const char* strLibName)
{
	auto itor = m_Libs.find(strLibName);
	if (itor == m_Libs.end())
	{
		return nullptr;
	}
	return std::dynamic_pointer_cast<I_Lib>(itor->second);
}


void	C_Interface::WaitQuit() 
{
	for (auto pair : m_Libs)
	{
		m_WaitDelLibs.push_back(pair.second);
	}
	m_Libs.clear();

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
