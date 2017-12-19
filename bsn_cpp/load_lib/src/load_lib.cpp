#include "load_lib.h"
#include "lib.h"

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include <bsn_cpp/include/name_space.h>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////
C_LoadLib::C_LoadLib()
	: m_spI_Global(nullptr)
	, m_spI_Log(nullptr)
{

}

C_LoadLib::~C_LoadLib() {
	m_spI_Log 		= nullptr;
	m_spI_Global 	= nullptr;
}

void 
C_LoadLib::SetGlobal(D_N1(global)::I_Global::T_SPI_Global spI_Global) {
	m_spI_Global 	= spI_Global;
	m_spI_Log 		= m_spI_Global->GetLog();
}

C_LoadLib::T_SPI_LoadLib
C_LoadLib::GetSPI_LoadLib() {
	return shared_from_this();
}

I_Lib::T_SPI_Lib	
C_LoadLib::Load(
	const char* strLibName
	, const char* strLibPath
	, const char* strDebugSuffix
	, const char* strReleaseSuffix
) {
	D_LogInfoF(m_spI_Log, "strLibName=%s,strLibPath=%s,strDebugSuffix=%s,strReleaseSuffix=%s"
		, strLibName
		, strLibPath
		, strDebugSuffix
		, strReleaseSuffix
	);

	auto spC_Lib = C_Lib::NewC_Lib();
	spC_Lib->SetGlobal(m_spI_Global);
	spC_Lib->SetName(strLibName);
 
	auto bLoadSuccess = spC_Lib->Open(strLibPath, strDebugSuffix, strReleaseSuffix, 0);
	if (!bLoadSuccess) {
		D_LogError(m_spI_Log, "!bLoadSuccess")
		return nullptr;
	}

	if (m_Libs.find(strLibName) != m_Libs.end()) {
		auto pOldLib = Get(strLibName);
		if (pOldLib && pOldLib.use_count() > 1) {
			D_LogWarn(m_spI_Log, "pOldLib using, wait del");
			m_WaitDelLibs.push_back(pOldLib);
		}
	}

	m_Libs[strLibName] = spC_Lib;
	D_LogInfoF(m_spI_Log, "%p"
		, spC_Lib.get()
	);
	return spC_Lib->GetSPI_Lib();
}

I_Lib::T_SPI_Lib	
C_LoadLib::Get(const char* strLibName) {
	D_LogInfoF(
		m_spI_Log
		, "strLibName=%s"
		, strLibName
	);

	auto itor = m_Libs.find(strLibName);
	if (itor == m_Libs.end()) {
		D_LogWarnF(m_spI_Log, "not found %s", strLibName);
		return nullptr;
	}
	return itor->second;
}


void	
C_LoadLib::WaitQuit() {
	D_LogInfoF(
		m_spI_Log
		, "m_Libs.size()=%u"
		, m_Libs.size()
	);

	for (auto pair : m_Libs) {
		m_WaitDelLibs.push_back(pair.second);
	}
	m_Libs.clear();

	D_LogInfo(m_spI_Log, "m_spI_Log = nullptr");
	m_spI_Log = nullptr;

	auto itor = m_WaitDelLibs.begin();
	for (; itor != m_WaitDelLibs.end(); ) {
		while ((*itor).use_count() > 1) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		++itor;
		m_WaitDelLibs.pop_front();
	}
}
//////////////////////////////////////////////////////////////////////
C_LoadLib* 
CreateCLoadLib() {
	C_LoadLib* imp = New<C_LoadLib>();
	return imp;
}

void 
ReleaseCLoadLib(I_LoadLib* iLoadLib) {
	C_LoadLib* pImp = static_cast<C_LoadLib*>(iLoadLib);
	Delete(pImp);
}

C_LoadLib::T_SPC_LoadLib
C_LoadLib::NewC_LoadLib() {
	auto spC_LoadLib = C_LoadLib::T_SPC_LoadLib(
		CreateCLoadLib()
		, ReleaseCLoadLib
	);
	return spC_LoadLib;
}

C_LoadLib::T_SPI_LoadLib
C_LoadLib::NewI_LoadLib() {
	auto spC_LoadLib = C_LoadLib::NewC_LoadLib();
	return spC_LoadLib->GetSPI_LoadLib();
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif