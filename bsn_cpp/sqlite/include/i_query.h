#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <iostream>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

class I_Query {
public:
 	typedef std::shared_ptr<I_Query> T_SPI_Query;

public:
	virtual int 
		GetInt(char const* strColumnName, int iNullValue) = 0;
	virtual int 
		GetInt(int nColumn, int iNullValue) = 0;

	virtual double 
		GetDouble(char const* strColumnName,  double dNullValue) = 0;
	virtual double 
		GetDouble(int nColumn, double  dNullValue) = 0;

	virtual const char* 
		GetText(char const* strColumnName, char const* strNullValue) = 0;
	virtual const char* 
		GetText(int nColumn, char const*  strNullValue)= 0;

	virtual const uint8_t* 
		GetBlob(char const* strColumnName, int& nLen) = 0;
	virtual const uint8_t* 
		GetBlob(int nColumn, int& nLen) = 0;

	virtual bool 
		ColumnIsNull(char const* strColumnName) = 0;
	virtual bool 
		ColumnIsNull(int nColumn) = 0;

	virtual int
		ColumnDataType(int nColumn) = 0;
	virtual char const*
		ColumnDeclType(int nColumn) = 0;

	virtual int 
		ColumnIndex(char const* strColumnName) = 0;
	virtual char const*
		ColumnName(int nColumn) = 0;

	virtual bool 
		Eof() = 0;
	virtual bool 
		FetchRow() = 0;
	virtual int 
		EffectRow() = 0;
	virtual int 
		ColumnCount() = 0;

protected:
	virtual ~I_Query() = default;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End