#pragma once

#include "./../include/i_stmt.h"
#include "db.h"
#include "query.h"

#include <sqlite3.h>

#include <stdarg.h>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////
class C_Stmt : public I_Stmt {
public:
	typedef std::shared_ptr<C_Stmt> T_SPC_Stmt;	

public:
	virtual bool
		Compile(char const* strSql) override;

	virtual bool
		Reset() override;

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
		
	virtual I_Query* 
		Query() override;

public:
	C_Stmt(C_DB::T_SPC_DB& spC_DB);
	virtual ~C_Stmt();

public:
	C_DB::T_SPC_DB 	m_spC_DB;
	C_Query 		m_Query;
	sqlite3_stmt* 	m_pStmt;
	std::string 			m_strSql;

public:
	bool 
		Finalize();
	bool
		Compile();
	bool
		Step();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End