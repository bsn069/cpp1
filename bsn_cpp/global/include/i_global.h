#pragma once

#include <bsn_cpp/common/include/i_common.h>
#include <bsn_cpp/common/include/i_alloc.h>
#include <bsn_cpp/load_lib/include/i_load_lib.h>
#include <bsn_cpp/log/include/i_log.h>
#include <bsn_cpp/net/include/i_net.h>
#include <bsn_cpp/sqlite/include/i_db.h>
#include <bsn_cpp/input/include/i_input.h>

#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>

#include <stdint.h>
#include <memory>
#include <string>

D_BsnNamespace1(global)
//////////////////////////////////////////////////////////////////////

class I_Global : public std::enable_shared_from_this<I_Global>{
public:
	typedef std::shared_ptr<I_Global> T_SPI_Global;

public:
	virtual void 
		Run() = 0;
	virtual T_SPI_Global
		GetSPI_Global() = 0;

	virtual D_N1(common)::I_Common::T_SPI_Common
		GetCommon() = 0;
	virtual D_N1(common)::I_Alloc::T_SPI_Alloc
		GetAllocRaw() = 0;
	virtual D_N1(load_lib)::I_LoadLib::T_SPI_LoadLib
		GetLoadLib() = 0;
	virtual D_N1(log)::I_Log::T_SPI_Log
		GetLog() = 0;
	virtual D_N1(net)::I_Net::T_SPI_Net
		GetNet() = 0;
	virtual D_N1(sqlite)::I_DB::T_SPI_DB
		GetSqlite() = 0;
	virtual D_N1(input)::I_Input::T_SPI_Input
		GetInput() = 0;

protected:
	virtual ~I_Global() = default;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End