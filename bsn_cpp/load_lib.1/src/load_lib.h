#pragma once

#include "./../include/i_load_lib.h"
#include "./lib.h"

#include <map>
#include <list>

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////
class C_LoadLib : public I_LoadLib
{
public:
	typedef std::shared_ptr<C_LoadLib> T_SPC_LoadLib;	
	typedef std::map<std::string, I_Lib::T_SPI_Lib> T_Libs;
	typedef std::list<I_Lib::T_SPI_Lib> T_WaitDelLibs;

	
public:
	virtual T_SPI_Lib	Load(
		const char* strLibName
		, const char* strLibPath
		, const char* strDebugSuffix
		, const char* strReleaseSuffix
	) override;
	virtual T_SPI_Lib	Get(const char* strLibName) override;
	virtual void 		SetLog(T_SPI_Log iLog) override
	{
		m_iLog = iLog;
	}; 
	virtual void		WaitQuit() override;

public:
	C_LoadLib();
	virtual ~C_LoadLib();


private:
	T_SPI_Log 		m_iLog;
	T_Libs 			m_Libs;
	T_WaitDelLibs 	m_WaitDelLibs;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End