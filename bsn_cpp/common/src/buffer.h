#pragma once

#include "./../include/i_buffer.h"
#include "./../include/i_alloc.h"

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

#include <stdint.h>

D_BsnNamespace1(common)
//////////////////////////////////////////////////////////////////////
class C_Buffer : public I_Buffer 
{
public:
	virtual uint32_t 
		GetCapacity() override;

	virtual uint8_t* 
		GetReadPtr() override;
	virtual uint32_t 
		GetCanReadLength() override;

	virtual uint8_t* 
		GetWritePtr() override;
	virtual uint32_t 
		GetCanWriteLength() override;

	virtual bool 
		MakeCanWriteLength(uint32_t) override;
	virtual bool 
		Write(uint8_t const*, uint32_t) override;
	
	virtual bool 
		Read(uint32_t) override;
	virtual void 
		Write(uint32_t) override;

public:
	C_Buffer(I_Alloc::T_SPI_Alloc, uint32_t);
	virtual ~C_Buffer();

protected:
	bool Realloc(uint32_t);

protected:
	uint8_t*	m_pData;
	uint32_t	m_u32Capacity;
	uint32_t	m_u32WritePos;
	uint32_t	m_u32InitSize;
	I_Alloc::T_SPI_Alloc		m_spI_Alloc;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 

