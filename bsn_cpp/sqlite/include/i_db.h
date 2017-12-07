#pragma once

#include "i_stmt.h"

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <string>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

class I_DB : public std::enable_shared_from_this<I_DB>{
public:
	typedef std::shared_ptr<I_DB> T_SPI_DB;

public:
	virtual bool 
		Open(std::string const& strDBFile) = 0;
	virtual bool 
		Close() = 0;

	virtual I_Stmt::T_SPI_Stmt
		NewStmt() = 0;
	virtual bool 
		Exec(char const* szSql) = 0;

	virtual std::string const& 
		GetName() const = 0;
	virtual uint64_t 
		LastInsertRowId() = 0;
	virtual int 
		EffectRow() = 0;
		
protected:
	virtual ~I_DB() = default;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End