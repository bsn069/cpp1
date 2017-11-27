#pragma once

#include "./../include/buffer.h"

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/i_alloc.h>

#include <stdint.h>

D_BsnNamespace1(common)
//////////////////////////////////////////////////////////////////////
class C_Buffer : I_Buffer 
{
public:
	virtual uint32_t GetCapacity() override;

	virtual uint8_t* GetReadPtr() override;
	virtual uint32_t GetCanReadLength() override;

	virtual uint8_t* GetWritePtr() override;
	virtual uint32_t GetCanWriteLength() override;

	virtual bool MakeCanWriteLength(uint32_t u32Len) override;
	virtual bool Write(uint8_t const* pBuf, uint32_t u32Len) override;
	
	virtual bool Read(uint32_t u32Len) override;
	virtual void Write(uint32_t u32Len) override;

public:
	Buffer(NBsn::I_Alloc::T_SPI_Alloc spI_Alloc, uint32_t u32InitSize);
	~Buffer();

protected:
	bool Realloc(uint32_t u32Len);

protected:
	NBsn::I_Alloc::T_SPI_Alloc		m_spI_Alloc;
	uint8_t*	m_pData;
	uint32_t	m_u32Capacity;
	uint32_t	m_u32WritePos;
	uint32_t	m_u32InitSize;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 

