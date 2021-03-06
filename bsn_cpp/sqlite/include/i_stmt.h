#pragma once

#include "i_query.h"
#include "column_ex.h"

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <iostream>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

class I_Stmt: public std::enable_shared_from_this<I_Stmt> {
public:
 	typedef std::shared_ptr<I_Stmt> T_SPI_Stmt;

public:
	virtual bool
		Compile(char const* strSql) = 0;

	virtual bool
		Reset() = 0;

    virtual bool 
		Bind(int iIndex, int value) = 0;
    virtual bool 
		Bind(int iIndex, int64_t value) = 0;
    virtual bool 
		Bind(int iIndex, double value) = 0;
    virtual bool 
		Bind(int iIndex) = 0;
    virtual bool 
		Bind(int iIndex, std::string& value) = 0;
    virtual bool 
		Bind(int iIndex, char const* value) = 0;
    virtual bool 
		Bind(int iIndex, uint8_t const* value, uint32_t u32Len) = 0;

	virtual bool 
		BindNull(int iIndex) = 0;	
	virtual bool 
		BindText(int iIndex, char const* value) = 0;
	virtual bool 
		BindString(int iIndex, std::string& value) = 0;
	virtual bool 
		BindBlob(int iIndex, uint8_t const* value, uint32_t u32Len) = 0;
	virtual bool 
		BindDouble(int iIndex, double value) = 0;
	virtual bool 
		BindInt(int iIndex, int value) = 0;
	virtual bool 
		BindInt64(int iIndex, int64_t value) = 0;

	virtual I_Query* 
		Query() = 0;
	virtual C_ColumnEx
		GetC_ColumnEx(int iIndex) = 0;

protected:
	virtual ~I_Stmt() = default;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End