#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <iostream>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

class I_Stmt {
public:
 	typedef std::shared_ptr<I_Stmt> T_SPI_Stmt;


public:
	virtual bool 
		BindText(int iIndex, char* pData);

protected:
	virtual ~I_Stmt() = default;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End