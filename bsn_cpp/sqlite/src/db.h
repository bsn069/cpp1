#pragma once

#include "./../include/i_db.h"
#include "./../include/i_stmt.h"
 
#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/log/include/i_log.h>

#include <sqlite3.h>

#include <stdarg.h>
#include <string>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////
class C_DB : public I_DB {
public:
	typedef std::shared_ptr<C_DB> T_SPC_DB;	

public:
	virtual char const*
		Ver() const override;
	virtual int
		VerNum() const override;
	virtual char const*
		SourceId() const override;

	virtual char const*
		LibVer() const override;
	virtual int
		LibVerNum() const override;
	virtual char const*
		LibSourceId() const override;

 	virtual bool 
	 	Open(
			char const* szDBFile
			, E_OpenType eOpenType
		) override;
	virtual bool 
		Close() override;

	virtual I_Stmt::T_SPI_Stmt
		NewStmt() override;
	virtual int 
		Exec(char const* szSql) override;

	virtual std::string const& 
		GetName() const override;

	virtual uint64_t 
		LastInsertRowId() override;
 	virtual int 
		EffectRow() override;
	virtual uint64_t 
		TotalEffectRow() override;	

	virtual int 
		GetErrCode() override;	
	virtual int 
		GetExErrCode() override;	
	virtual char const* 
		GetErrMsg() override;	

public:
	void 
		SetLog(D_N1(log)::I_Log::T_SPI_Log spI_Log) {
			m_spI_Log = spI_Log;
		};
	void 
		SetLib(D_N1(load_lib)::I_Lib::T_SPI_Lib spI_Lib) {
			m_spI_Lib = spI_Lib;
		};
	int
		GetSqliteOpenType(E_OpenType eOpenType);

public:
	C_DB();
	virtual ~C_DB();

public:
	D_N1(log)::I_Log::T_SPI_Log m_spI_Log;
	D_N1(load_lib)::I_Lib::T_SPI_Lib 	m_spI_Lib;
	sqlite3* 	m_pDB;
	std::string 		m_strDBFileName;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End