#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(input)
//////////////////////////////////////////////////////////////////////
class I_Input : public std::enable_shared_from_this<I_Input> {
public:
	typedef std::shared_ptr<I_Input> T_SPI_Input;
	
public:

protected:
	virtual ~I_Input() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End