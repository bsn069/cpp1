#pragma once

#include "i_alloc.h"

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

#include <memory>
 
D_BsnNamespace1(common)
//////////////////////////////////////////////////////////////////////
class I_Common
{
public:
	typedef std::shared_ptr<I_Common> T_SPI_Common;

public:
	virtual D_N1(common)::I_Buffer::T_SPI_Buffer NewBuffer(D_N1(common)::I_Alloc::T_SPI_Alloc spI_Alloc, uint32_t u32InitSize) = 0;
	virtual D_N1(common)::I_Alloc::T_SPI_Alloc NewAlloc(D_N1(common)::I_Alloc::E_Type type) = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
