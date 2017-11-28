#include "common.h"
#include "alloc_raw.h"
#include "buffer.h"

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
	for (auto& spI_Alloc : m_alloc) {
		spI_Alloc.reset();
	}
}

D_FunImp I_Buffer* 
CreateCBuffer(
	I_Alloc::T_SPI_Alloc spI_Alloc
	, uint32_t u32InitSize
) {
	C_Buffer* imp = New<C_Buffer>(spI_Alloc, u32InitSize);
	return imp;
}

D_FunImp void 
ReleaseCBuffer(I_Buffer* iBuffer) {
	C_Buffer* pImp = static_cast<C_Buffer*>(iBuffer);
	Delete(pImp);
}
		
I_Buffer::T_SPI_Buffer  
C_Common::NewBuffer(
	I_Alloc::T_SPI_Alloc spI_Alloc
	, uint32_t u32InitSize
) {
	return I_Buffer::T_SPI_Buffer(
		CreateCBuffer(spI_Alloc, u32InitSize)
		, ReleaseCBuffer
	);
}

D_FunImp I_Alloc* 
CreateCAllocRaw() {
	C_AllocRaw* imp = New<C_AllocRaw>();
	return imp;
}

D_FunImp void 
ReleaseCAllocRaw(I_Alloc* iAlloc) {
	C_AllocRaw* pImp = static_cast<C_AllocRaw*>(iAlloc);
	Delete(pImp);
}

I_Alloc::T_SPI_Alloc 
C_Common::NewAlloc(I_Alloc::E_Type eType) {
	return I_Alloc::T_SPI_Alloc(
		CreateCAllocRaw()
		, ReleaseCAllocRaw
	);
}

void 
C_Common::SetGlobalAlloc(I_Alloc::T_SPI_Alloc spI_Alloc) {
	D_Assert(spI_Alloc);
	m_alloc[spI_Alloc->GetType()] = spI_Alloc;
}

I_Alloc::T_SPI_Alloc 
C_Common::GetGlobalAlloc(I_Alloc::E_Type eType) {
	return m_alloc[eType];
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End