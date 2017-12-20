#pragma once

#include "./../include/i_load_lib.h"
 
#include <bsn_cpp/global/include/i_global.h>
#include <bsn_cpp/log/include/i_log.h>

#include <bsn_cpp/include/name_space.h>

#include <stdarg.h>
#include <map>
#include <list>

D_BsnNamespace1(load_lib)
//////////////////////////////////////////////////////////////////////
class C_LoadLib : public I_LoadLib {
public:
	typedef std::shared_ptr<C_LoadLib> T_SPC_LoadLib;	
	typedef std::map<std::string, I_Lib::T_SPI_Lib> T_Libs;
	typedef std::list<I_Lib::T_SPI_Lib> T_WaitDelLibs;

public:
 	static T_SPC_LoadLib
		NewC_LoadLib();
	static T_SPI_LoadLib
		NewI_LoadLib();

public:
	virtual I_Lib::T_SPI_Lib	
		Load(
			const char* strLibName
			, const char* strLibPath
			, const char* strDebugSuffix
			, const char* strReleaseSuffix
		) override;
	virtual I_Lib::T_SPI_Lib	
		Get(const char* strLibName) override;

	virtual void 
		Init() override;
	virtual void 
		Start() override;
	virtual void 
		Quit() override;
	virtual void		
		UnInit() override;

public:
	void 
		SetGlobal(D_N1(global)::I_Global::T_SPI_Global spI_Global);
	T_SPI_LoadLib
		GetSPI_LoadLib();

public:
	C_LoadLib();
	virtual ~C_LoadLib();

private:
	D_N1(global)::I_Global::T_SPI_Global m_spI_Global;
	D_N1(log)::I_Log::T_SPI_Log m_spI_Log;
	
	T_Libs 			m_Libs;
	T_WaitDelLibs 	m_WaitDelLibs;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End