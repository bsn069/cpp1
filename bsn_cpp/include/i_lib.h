#pragma once

#include "name_space.h"
#include <memory>
 
class I_Lib
{
public:
	typedef std::shared_ptr<I_Lib> T_SPI_Lib;

public:
	virtual void* 		Func(const char* strFuncName) = 0;
	virtual const char* Name() = 0;
};
 
