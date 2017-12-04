#pragma once

#include "./../include/i_stmt.h"
 
#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/log/include/i_log.h>

#include <sqlite3.h>

#include <stdarg.h>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////
class C_Stmt : public I_Stmt {
public:
	typedef std::shared_ptr<C_Stmt> T_SPC_Stmt;	

public:
	virtual bool 
		BindNull(int iIndex);	
	virtual bool 
		BindText(int iIndex, char const* value) override;
	virtual bool 
		BindBlob(int iIndex, uint8_t const* value, uint32_t u32Len) override;
	virtual bool 
		BindDouble(int iIndex, double value) override;
	virtual bool 
		BindInt(int iIndex, int value) override;

 	virtual bool 
		Reset() override;
	virtual bool
		Compile() override;

public:
	C_Stmt();
	virtual ~C_Stmt();

public:
	string 			m_strSql;
	C_DB::T_SPC_DB 	m_spC_DB;
	sqlite3_stmt* 	m_pStmt;

private:
	bool 
		Finalize();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End