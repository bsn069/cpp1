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
		Count,
	};

public:
    virtual E_Type 
		GetType() const = 0;

    virtual void* 
		Malloc(size_t) = 0;
    virtual void* 
		Realloc(void*, size_t) = 0;
    virtual void  
		Free(void*) = 0;
 
    virtual void* 
		MallocTrack(
			size_t
			, char const * const
			, char const * const
			, uint32_t
		) = 0;
    virtual void* 
		ReallocTrack(
			void*
			, size_t
			, char const * const
			, char const * const
			, uint32_t
		) = 0;
    virtual void  
		FreeTrack(void*) = 0;

protected:
	virtual ~I_Alloc() = default;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

