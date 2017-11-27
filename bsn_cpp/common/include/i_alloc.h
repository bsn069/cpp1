#pragma once
 
#include "d_alloc.h"

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

#include <memory>
 
D_BsnNamespace1(common)
//////////////////////////////////////////////////////////////////////
class I_Alloc {
public:
	typedef std::shared_ptr<I_Alloc> T_SPI_Alloc;
	enum E_Type {
		Raw = 0,
	}

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

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

