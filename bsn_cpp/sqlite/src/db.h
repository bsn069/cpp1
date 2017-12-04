#pragma once

#include "./../include/i_db.h"
 
#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/log/include/i_log.h>

#include <sqlite3.h>

#include <stdarg.h>

D_BsnNamespace1(db)
//////////////////////////////////////////////////////////////////////
class C_DB : public I_DB {
public:
	typedef std::shared_ptr<C_DB> T_SPC_DB;	

public:
 	virtual bool 
	 	Open(std::string const& strDBFile) override;
	virtual bool 
		Close() override;

	virtual string const& 
		GetName() const override;

public:
	void 
		SetLog(D_N1(log)::I_Log::T_SPI_Log spI_Log) {
			m_spI_Log = spI_Log;
		};
	void 
		SetLib(D_N1(load_lib)::I_Lib::T_SPI_Lib spI_Lib) {
			m_spI_Lib = spI_Lib;
		};

public:
	C_DB();
	virtual ~C_DB();

public:
	D_N1(log)::I_Log::T_SPI_Log m_spI_Log;
	D_N1(load_lib)::I_Lib::T_SPI_Lib 	m_spI_Lib;
	sqlite3* 	m_pDB;
	string 		m_strName;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End