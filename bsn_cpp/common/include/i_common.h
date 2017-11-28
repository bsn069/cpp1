#pragma once

#include "i_alloc.h"
#include "i_buffer.h"

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
	virtual I_Buffer::T_SPI_Buffer 
		NewBuffer(I_Alloc::T_SPI_Alloc, uint32_t) = 0;
	virtual I_Alloc::T_SPI_Alloc 
		NewAlloc(I_Alloc::E_Type) = 0;

	virtual void 
		SetGlobalAlloc(I_Alloc::T_SPI_Alloc) = 0;
	virtual I_Alloc::T_SPI_Alloc 
		GetGlobalAlloc(I_Alloc::E_Type) = 0;

protected:
	virtual ~I_Common() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
