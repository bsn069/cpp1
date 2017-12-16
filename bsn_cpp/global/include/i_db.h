#pragma once

#include "i_stmt.h"
#include "i_column.h"

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <string>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

class I_DB : public std::enable_shared_from_this<I_DB>{
public:
	typedef std::shared_ptr<I_DB> T_SPI_DB;
	enum E_OpenType {
		E_OpenType_ReadOnly = 0,
		E_OpenType_ReadWrite,
		E_OpenType_Create,
		E_OpenType_Uri,
		E_OpenType_Memery,
		E_OpenType_Count,
	};

public:
	virtual char const*
		Ver() const = 0;
	virtual int
		VerNum() const = 0;
	virtual char const*
		SourceId() const = 0;

	virtual char const*
		LibVer() const = 0;
	virtual int
		LibVerNum() const = 0;
	virtual char const*
		LibSourceId() const = 0;

	virtual bool 
		Open(
			char const* szDBFile
			, E_OpenType eOpenType
		) = 0;
	virtual bool 
		Close() = 0;

	virtual I_Stmt::T_SPI_Stmt
		NewStmt() = 0;
	//Shortcut to execute one or multiple SQL statements without results (UPDATE, INSERT, ALTER, COMMIT, CREATE...).
	virtual int 
		Exec(char const* szSql) = 0;
	//Shortcut to execute a one step query and fetch the first column of the result
	// virtual I_Column
	// 	ExecAndGet(char const* szSql) = 0;

	virtual std::string const& 
		GetName() const = 0;
	virtual uint64_t 
		LastInsertRowId() = 0;
	virtual int 
		EffectRow() = 0;
	// Get total number of rows modified by all INSERT, UPDATE or DELETE statement since connection.
	virtual uint64_t 
		TotalEffectRow() = 0;

	// Return the numeric result code for the most recent failed API call (if any).
	virtual int 
		GetErrCode() = 0;	
	// Return the extended numeric result code for the most recent failed API call (if any).
	virtual int 
		GetExErrCode() = 0;	
	// Return UTF-8 encoded English language explanation of the most recent failed API call (if any).
	virtual char const* 
		GetErrMsg() = 0;	
		
protected:
	virtual ~I_DB() = default;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End