#include "load_lib.h"

#include <bsn_cpp/log/include/i_log.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////
C_LoadLib::C_LoadLib() {	
	D_LogInfo(m_iLog, "");
}


C_LoadLib::~C_LoadLib() {
	D_LogInfo(m_iLog, "");
}

D_FunImp I_Lib* 
CreateCLib() {
	C_Lib* imp = New<C_Lib>();
	return imp;
}

D_FunImp void 
ReleaseCLib(I_Lib* iLib) {
	C_Lib* pImp = static_cast<C_Lib*>(iLib);
	Delete(pImp);
}

I_Lib::T_SPI_Lib	
C_LoadLib::Load(
	const char* strLibName
	, const char* strLibPath
	, const char* strDebugSuffix
	, const char* strReleaseSuffix
) {
	D_LogInfoF(m_iLog, "strLibName=%s,strLibPath=%s,strDebugSuffix=%s,strReleaseSuffix=%s"
		, strLibName
		, strLibPath
		, strDebugSuffix
		, strReleaseSuffix
	);

	auto pLibI = std::shared_ptr<I_Lib>(CreateCLib(), ReleaseCLib);
	auto pLibC = std::dynamic_pointer_cast<C_Lib>(pLibI);
	pLibC->SetLog(m_iLog);
	pLibC->SetName(strLibName);
	auto bLoadSuccess = pLibC->Open(strLibPath, strDebugSuffix, strReleaseSuffix, 0);
	if (!bLoadSuccess)
	{
		D_LogError(m_iLog, "!bLoadSuccess")
		return nullptr;
	}

	if (m_Libs.find(strLibName) != m_Libs.end()) {
		auto pOldLib = this->Get(strLibName);
		if (pOldLib && pOldLib.use_count() > 1)
		{
			D_LogWarn(m_iLog, "pOldLib using, wait del");
			m_WaitDelLibs.push_back(pOldLib);
		}
	}

	m_Libs[strLibName] = pLibC;
	D_LogInfoF(m_iLog, "%p"
		, pLibC.get()
	);
	return pLibI;
}

I_Lib::T_SPI_Lib	
C_LoadLib::Get(const char* strLibName) {
	D_LogInfoF(
		m_iLog
		, "strLibName=%s"
		, strLibName
	);

	auto itor = m_Libs.find(strLibName);
	if (itor == m_Libs.end()) {
		D_LogWarnF(m_iLog, "not found %s", strLibName);
		return nullptr;
	}
	return itor->second;
}


void	
C_LoadLib::WaitQuit() {
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

 
