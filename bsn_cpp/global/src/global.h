#pragma once

#include "./../include/i_global.h"
 
#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>

#include <stdarg.h>
#include <string>

D_BsnNamespace1(global)
//////////////////////////////////////////////////////////////////////
class C_Global : public I_Global {
public:
	typedef std::shared_ptr<C_Global> T_SPC_Global;	

	static T_SPI_Global
		NewI_Global();

public:
	virtual void Run() override;

	virtual D_N1(common)::I_Common::T_SPI_Common
		GetCommon() override;
	virtual D_N1(common)::I_Alloc::T_SPI_Alloc
		GetAllocRaw() override;
	virtual D_N1(load_lib)::I_LoadLib::T_SPI_LoadLib
		GetLoadLib() override;
	virtual D_N1(log)::I_Log::T_SPI_Log
		GetLog() override;
	virtual D_N1(net)::I_Net::T_SPI_Net
		GetNet() override;
	virtual D_N1(sqlite)::I_DB::T_SPI_DB
		GetSqlite() override;

public:
 	D_N1(common)::I_Common::T_SPI_Common 		m_spI_Common;
	D_N1(common)::I_Alloc::T_SPI_Alloc 			m_spI_AllocRaw;
	D_N1(load_lib)::I_LoadLib::T_SPI_LoadLib	m_spI_LoadLib;
	D_N1(log)::I_Log::T_SPI_Log 				m_spI_Log;
	D_N1(net)::I_Net::T_SPI_Net 				m_spI_Net;
	D_N1(sqlite)::I_DB::T_SPI_DB				m_spI_Sqlite;

	uint32_t 									m_u32FrameMS;
	boost::asio::io_service 					m_ioService;
	boost::asio::deadline_timer 				m_updateTimer;

public:
	C_Global();
	virtual ~C_Global();

private:
	void Init();
	void UnInit();
	void WaitUpdate();
	void Update(const boost::system::error_code& ec);
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End