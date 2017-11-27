#pragma once

#include "./../include/i_common.h"

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/i_alloc.h>

#include <stdint.h>

D_BsnNamespace1(common)
//////////////////////////////////////////////////////////////////////
class C_Common : I_Common 
{
public:
	virtual D_N1(common)::I_Buffer::T_SPI_Buffer NewBuff(D_N1(common)::I_Alloc::T_SPI_Alloc spI_Alloc, uint32_t u32InitSize) override;
	virtual D_N1(common)::I_Alloc::T_SPI_Alloc NewAlloc(D_N1(common)::I_Alloc::E_Type type) override;
	
public:
	C_Common();
	~C_Common();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 

