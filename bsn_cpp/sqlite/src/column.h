#pragma once

#include "./../include/i_column.h"
#include "stmt.h"
 
#include <sqlite3.h>

#include <stdarg.h>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////
class C_Column : public I_Column {
public:
 	typedef std::shared_ptr<C_Column> T_SPC_Column;
	static T_SPC_Column
		NewC_Column(C_Stmt::T_SPC_Stmt& spC_Stmt, int index);
	static T_SPI_Column
		NewI_Column(C_Stmt::T_SPC_Stmt& spC_Stmt, int index);

public:
	virtual char const* 
		GetName() const override;
	virtual char const* 
		GetDeclType() const override;
	virtual E_DataType 
		GetDataType() const override;
	virtual int 
		Size() const override;	 
	virtual int 
		Index() const override;

	virtual int32_t 
		GetInt32() const override;
	virtual int64_t 
		GetInt64() const override;
	virtual double 
		GetDouble() const override;
 	virtual char const* 
		GetText() const override;
 	virtual std::string 
		GetString() const override;
 	virtual uint8_t const* 
		GetBlob() const override;


public:
	C_Column(C_Stmt::T_SPC_Stmt spC_Stmt, int index);
	virtual ~C_Column();

public:
	C_Stmt::T_SPC_Stmt m_spC_Stmt;
	int8_t 	m_index;

public:
	sqlite3_stmt* 
		Stmt() const;
	int 
		GetRawDataType() const;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End