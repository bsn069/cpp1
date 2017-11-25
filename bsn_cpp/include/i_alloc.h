#pragma once

#include "d_alloc.h"
#include <stdint.h>

namespace N_Bsn
{

class I_Alloc {
public:
    virtual void* Malloc(size_t size) = 0;
    virtual void* Realloc(void* ptr, size_t size) = 0;
    virtual void  Free(void* ptr) = 0;
 
    virtual void* MallocTrack(
		size_t size
		, char const * const file
		, char const * const func
		, uint32_t line
	) = 0;
    virtual void* ReallocTrack(
		void* ptr
		, size_t size
		, char const * const file
		, char const * const func
		, uint32_t line
	) = 0;
    virtual void  FreeTrack(void* ptr) = 0;
};

}

