#include "buffer.h"

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

#include <stdint.h>
#include <string.h>

D_BsnNamespace1(common)
//////////////////////////////////////////////////////////////////////


C_Buffer::C_Buffer(
	I_Alloc::T_SPI_Alloc spI_Alloc
	, uint32_t u32InitSize
)
    : m_pData(nullptr)
    , m_u32Capacity(0)
    , m_u32WritePos(0)
    , m_u32InitSize(u32InitSize)
    , m_spI_Alloc(spI_Alloc)
{
	Realloc(m_u32InitSize);
}


C_Buffer::~C_Buffer() {
    if (m_pData) {
		D_Free(m_spI_Alloc, m_pData);
    }
    m_spI_Alloc = nullptr;
    m_u32Capacity = 0;
    m_u32WritePos = 0;
	m_u32InitSize = 0;
}

bool 
C_Buffer::Realloc(uint32_t u32Len) {
    D_Assert(u32Len > m_u32Capacity);
    D_Assert(m_spI_Alloc);

    uint8_t* pBuf = reinterpret_cast<uint8_t*>(D_Realloc(m_spI_Alloc, m_pData, u32Len));
    D_Assert(pBuf);
	if (pBuf == nullptr)
	{
		return false;
	}

	m_u32Capacity = u32Len;
	m_pData = pBuf;
	return true;
}

uint8_t* 
C_Buffer::GetWritePtr() {
    return (m_pData + m_u32WritePos);
}

uint8_t* 
C_Buffer::GetReadPtr() {
    return m_pData;
}

uint32_t 
C_Buffer::GetCapacity() {
    return m_u32Capacity;
}

uint32_t 
C_Buffer::GetCanReadLength() {
    return m_u32WritePos;
}

uint32_t 
C_Buffer::GetCanWriteLength() {
    return (GetCapacity() - m_u32WritePos);
}

bool 
C_Buffer::Read(uint32_t u32Len) {
	D_Assert(u32Len > 0);
    D_Assert(m_spI_Alloc);
    D_Assert(u32Len <= GetCanReadLength());

    if (u32Len >= GetCanReadLength()) {
        if (m_pData && GetCapacity() > (m_u32InitSize * 2)) { // too long clear
			D_Free(m_spI_Alloc, m_pData);
            m_u32Capacity = 0;
        }
		m_u32WritePos = 0;        
    } else {
        memmove(m_pData, (m_pData + u32Len), (GetCanReadLength() - u32Len));
        m_u32WritePos -= u32Len;
    }

    return true;
}

bool 
C_Buffer::Write(uint8_t const* pBuf, uint32_t u32Len) {
	D_Assert(u32Len > 0);

    if (!MakeCanWriteLength(u32Len)) {  
		return false;
    }

    uint8_t* write_pos = GetWritePtr();
    memmove(write_pos, pBuf, u32Len);
    Write(u32Len);

    return true;
}

void 
C_Buffer::Write(uint32_t u32Len) {
	auto u32WritePos = m_u32WritePos + u32Len;
    D_Assert(u32WritePos <= GetCapacity());
	m_u32WritePos = u32WritePos;
}

bool 
C_Buffer::MakeCanWriteLength(uint32_t u32Len) {
    if (u32Len > GetCanWriteLength()) {  
		auto u32Inc = u32Len - GetCanWriteLength();     
        if (!Realloc(GetCapacity() + u32Inc)) {
            return false;
        }
    }

    return true;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End