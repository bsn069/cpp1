#pragma once

#include "./../include/i_common.h"

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

#include <stdint.h>

D_BsnNamespace1(common)
//////////////////////////////////////////////////////////////////////
class C_Common : public I_Common 
{
public:
	virtual I_Buffer::T_SPI_Buffer 
		NewBuffer(I_Alloc::T_SPI_Alloc, uint32_t) override;
	virtual I_Alloc::T_SPI_Alloc 
		NewAlloc(I_Alloc::E_Type) override;

	virtual void 
		SetGlobalAlloc(I_Alloc::T_SPI_Alloc) override;
	virtual I_Alloc::T_SPI_Alloc 
		GetGlobalAlloc(I_Alloc::E_Type) override;

public:
	C_Common();
	virtual ~C_Common();

public:
	I_Alloc::T_SPI_Alloc m_alloc[I_Alloc::Count];
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 

