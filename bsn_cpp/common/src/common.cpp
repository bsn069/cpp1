#pragma once

#include "common.h"

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <stdint.h>

D_BsnNamespace1(common)
//////////////////////////////////////////////////////////////////////

C_Common::C_Common() {
	
}

C_Common::~C_Common() {
 
}

D_FunImp I_Alloc* CreateCBuffer(D_N1(common)::I_Alloc::T_SPI_Alloc spI_Alloc, uint32_t u32InitSize)
{
	C_AllocRaw* imp = New<C_AllocRaw>(spI_Alloc, u32InitSize);
	return imp;
}

D_FunImp void ReleaseCBuffer(I_Alloc* iAlloc)
{
	C_AllocRaw* pImp = static_cast<C_AllocRaw*>(iAlloc);
	Delete(pImp);
}

D_N1(common)::I_Buffer::T_SPI_Buffer  C_Common::NewBuff(D_N1(common)::I_Alloc::T_SPI_Alloc spI_Alloc, uint32_t u32InitSize) {
	return D_N1(common)::I_Buffer::T_SPI_Buffer(CreateCBuffer(spI_Alloc, u32InitSize), ReleaseCBuffer);
}

D_FunImp I_Alloc* CreateCAllocRaw()
{
	C_AllocRaw* imp = New<C_AllocRaw>();
	return imp;
}

D_FunImp void ReleaseCAllocRaw(I_Alloc* iAlloc)
{
	C_AllocRaw* pImp = static_cast<C_AllocRaw*>(iAlloc);
	Delete(pImp);
}

D_N1(common)::I_Alloc::T_SPI_Alloc NewAlloc(D_N1(common)::I_Alloc::E_Type type) {
	return D_N1(common)::I_Alloc::T_SPI_Alloc(CreateCAllocRaw(), ReleaseCAllocRaw);
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End