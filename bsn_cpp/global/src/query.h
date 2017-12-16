#pragma once

#include "./../include/i_query.h"
 
#include <stdarg.h>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////
class C_Stmt;

class C_Query : public I_Query {
public:
	virtual int 
		GetInt(char const* strColumnName, int iNullValue) override;
	virtual int 
		GetInt(int nColumn, int iNullValue) override;

	virtual double 
		GetDouble(char const* strColumnName,  double dNullValue) override;
	virtual double 
		GetDouble(int nColumn, double  dNullValue) override;

	virtual const char* 
		GetText(char const* strColumnName, char const* strNullValue) override;
	virtual const char* 
		GetText(int nColumn, char const*  strNullValue)override;

	virtual const uint8_t* 
		GetBlob(char const* strColumnName, int& nLen) override;
	virtual const uint8_t* 
		GetBlob(int nColumn, int& nLen) override;

	virtual bool 
		ColumnIsNull(char const* strColumnName) override;
	virtual bool 
		ColumnIsNull(int nColumn) override;

	virtual int
		ColumnDataType(int nColumn) override;
	virtual char const*
		ColumnDeclType(int nColumn) override;

	virtual int 
		ColumnIndex(char const* strColumnName) override;
	virtual char const*
		ColumnName(int nColumn) override;

	virtual bool 
		Eof() override;
	virtual bool 
		FetchRow() override;
	virtual int 
		ColumnCount() override;

public:
	C_Query(C_Stmt* pC_Stmt);
	virtual ~C_Query();

public:
	C_Stmt* m_pC_Stmt;
	bool 	m_bEof;

public:
	void
		OnCompile();
	void
		OnReset();
	void
		OnFinalize();
	void
		Clear();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End