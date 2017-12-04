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


protected:
	virtual ~I_Query() = default;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End