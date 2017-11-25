#pragma once

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/i_alloc.h>

D_BsnNamespace1(loader)
//////////////////////////////////////////////////////////////////////

class C_AllocRaw : I_Alloc {
public:
    virtual void* Malloc(size_t size) override;

    virtual void* Realloc(void* ptr, size_t size) override;

    virtual void  Free(void* ptr) override;

    virtual void* MallocTrack(
		size_t size
		, char const * const file
		, char const * const func
		, uint32_t line
	) override;

    virtual void* ReallocTrack(
		void* ptr
		, size_t size
		, char const * const file
		, char const * const func
		, uint32_t line
	) override;

    virtual void  FreeTrack(void* ptr) override;
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
