#include "alloc_raw.h"

D_BsnNamespace1(common)
//////////////////////////////////////////////////////////////////////

C_AllocRaw::C_AllocRaw() 
	: m_eType(I_Alloc::Raw)
{

}

C_AllocRaw::~C_AllocRaw() {

}

I_Alloc::E_Type 
C_AllocRaw::GetType() const {
	return m_eType;
}

void* C_AllocRaw::Malloc(size_t size)
{
	return malloc(size);
}

void* C_AllocRaw::Realloc(void* ptr, size_t size)
{
	return realloc(ptr, size);
}

void C_AllocRaw::Free(void* ptr)
{
	free(ptr);
}

void* C_AllocRaw::MallocTrack(
	size_t size
	, char const * const file
	, char const * const func
	, uint32_t line
)
{
	return Malloc(size);
}

void* C_AllocRaw::ReallocTrack(
	void* ptr
	, size_t size
	, char const * const file
	, char const * const func
	, uint32_t line
)
{
	return Realloc(ptr, size);
}

void  C_AllocRaw::FreeTrack(void* ptr)
{
	Free(ptr);
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End