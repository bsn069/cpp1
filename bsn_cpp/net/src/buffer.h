#pragma once
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>
#include <stdint.h>
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
template<typename ALLOC>
class Buffer 
{
public:
	Buffer();
	~Buffer();

	bool  Init(ALLOC* alloc, uint32_t init_size);
	void  Release();
	uint8_t* GetWritePtr();
	uint8_t* GetReadPtr();

	uint32_t GetSize();
	uint32_t GetReadLength();
	uint32_t GetWriteSpace();

	bool Resize();
	bool Read(uint32_t len);
	void Write(uint32_t len);
	bool Write(const uint8_t* buf, uint32_t len);

protected:
	bool ReallocBuffer(uint32_t len);

protected:
	uint8_t*	m_pData;
	uint32_t	m_u32Capacity;
	uint32_t	m_u32Offset;
	uint32_t	m_u32InitSize;
	ALLOC*		m_pAlloc;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#include "buffer.hpp"

