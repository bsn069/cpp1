#pragma once

#include "./../include/i_stmt.h"
#include "./../include/column_ex.h"

#include "db.h"
#include "query.h"

#include <sqlite3.h>

#include <stdarg.h>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////
class C_Stmt : public I_Stmt {
public:
	typedef std::shared_ptr<C_Stmt> T_SPC_Stmt;	
	static T_SPC_Stmt
		NewC_Stmt(C_DB::T_SPC_DB& spC_DB);
	static T_SPI_Stmt
		NewI_Stmt(C_DB::T_SPC_DB& spC_DB);

public:
	virtual bool
		Compile(char const* strSql) override;

	virtual bool
		Reset() override;

    virtual bool 
		Bind(int iIndex, int value) override;
    virtual bool 
		Bind(int iIndex, int64_t value) override;
    virtual bool 
		Bind(int iIndex, double value) override;
    virtual bool 
		Bind(int iIndex) override;
    virtual bool 
		Bind(int iIndex, std::string& value) override;
    virtual bool 
		Bind(int iIndex, char const* value) override;
    virtual bool 
		Bind(int iIndex, uint8_t const* value, uint32_t u32Len) override;

	virtual bool 
		BindNull(int iIndex);	
	virtual bool 
		BindText(int iIndex, char const* value) override;
	virtual bool 
		BindString(int iIndex, std::string& value) override;
	virtual bool 
		BindBlob(int iIndex, uint8_t const* value, uint32_t u32Len) override;
	virtual bool 
		BindDouble(int iIndex, double value) override;
	virtual bool 
		BindInt(int iIndex, int value) override;
	virtual bool 
		BindInt64(int iIndex, int64_t value) override;
		
	virtual I_Query* 
		Query() override;
	virtual C_ColumnEx
		GetC_ColumnEx(int iIndex) override;

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
	T_SPC_Stmt
		GetSPC_Stmt();
	T_SPI_Stmt
		GetSPI_Stmt();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End