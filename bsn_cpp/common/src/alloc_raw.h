#pragma once

#include "./../include/i_alloc.h"

#include <bsn_cpp/include/name_space.h>

D_BsnNamespace1(common)
//////////////////////////////////////////////////////////////////////

class C_AllocRaw : public I_Alloc {
public:
    virtual E_Type 
		GetType() const override;

    virtual void* 
		Malloc(size_t) override;

    virtual void* 
		Realloc(void*, size_t) override;

    virtual void  
		Free(void*) override;

    virtual void* 
		MallocTrack(
			size_t 
			, char const * const
			, char const * const
			, uint32_t
		) override;

    virtual void* 
		ReallocTrack(
			void*
			, size_t
			, char const * const
			, char const * const
			, uint32_t
		) override;

    virtual void  
		FreeTrack(void*) override;

public:
	C_AllocRaw();
	virtual ~C_AllocRaw();

public:
	E_Type m_eType;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
