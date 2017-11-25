#include "alloc_raw.h"

D_BsnNamespace1(loader)
//////////////////////////////////////////////////////////////////////

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
	return Alloc(size);
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