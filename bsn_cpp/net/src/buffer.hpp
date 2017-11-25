#pragma once
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>
#include <stdint.h>
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////

namespace {
    static const uint32_t s_rem_u32Capacitythreshold = 128;
}

template<typename ALLOC>
Buffer<ALLOC>::Buffer()
    : m_pData(nullptr)
    , m_u32Capacity(0)
    , m_u32Offset(0)
    , m_u32InitSize(0)
    , m_pAlloc(nullptr)
{
}

template<typename ALLOC>
Buffer<ALLOC>::~Buffer() {
}

template<typename ALLOC>
bool Buffer<ALLOC>::Init(ALLOC* alloc, uint32_t init_size) {
    D_Assert(alloc);

    m_pAlloc = alloc;    
    m_u32InitSize = init_size;
    return ReallocBuffer(m_u32InitSize);
}

template<typename ALLOC>
void Buffer<ALLOC>::Release() {
    if (m_pData) {
        m_pAlloc->FreeBuf(m_pData);
        m_pData = nullptr;
    }
    m_pAlloc = nullptr;
    m_u32Capacity = 0;
    m_u32Offset = 0;
}

template<typename ALLOC> inline
uint8_t* Buffer<ALLOC>::GetWritePtr() {
    return (m_pData + m_u32Offset);
}

template<typename ALLOC> inline
uint8_t* Buffer<ALLOC>::GetReadPtr() {
    return m_pData;
}

template<typename ALLOC> inline
uint32_t Buffer<ALLOC>::GetSize() {
    return m_u32Capacity;
}

template<typename ALLOC> inline
uint32_t Buffer<ALLOC>::GetReadLength() {
    return m_u32Offset;
}

template<typename ALLOC> inline
uint32_t Buffer<ALLOC>::GetWriteSpace() {
    return (m_u32Capacity - m_u32Offset);
}

template<typename ALLOC> inline
bool Buffer<ALLOC>::Resize() {
    if ((m_u32Capacity - m_u32Offset) < s_rem_u32Capacitythreshold) {
        uint32_t size = (m_u32Capacity == 0) ? m_u32InitSize : (m_u32Capacity * 2);
        return ReallocBuffer(size);
    }

    return true;
}

template<typename ALLOC>
bool Buffer<ALLOC>::Read(uint32_t len) {
    if (len == 0) {
        return false;
    }

    D_Assert(m_pAlloc);
    D_Assert(len <= m_u32Offset);

    if (len >= m_u32Offset) {
        if (m_pData && m_u32Capacity > m_u32InitSize * 2) {
            m_pAlloc->FreeBuf(m_pData);
            m_pData = nullptr;
            m_u32Capacity = 0;
        }
        m_u32Offset = 0;
    } else {
        memmove(m_pData, (m_pData + len), (m_u32Offset - len));
        m_u32Offset -= len;
    }

    return true;
}

template<typename ALLOC> inline
void Buffer<ALLOC>::Write(uint32_t len) {
    D_Assert(m_u32Offset + len <= m_u32Capacity);
    if (m_u32Offset + len <= m_u32Capacity) {
        m_u32Offset += len;
    }
}


template<typename ALLOC>
bool Buffer<ALLOC>::Write(const uint8_t* buf, uint32_t len) {
    if (len == 0) {
        return true;
    }

    if (len > (m_u32Capacity - m_u32Offset)) {       
        if (!ReallocBuffer(m_u32Offset + len)) {
            return false;
        }
    }

    uint8_t* write_pos = m_pData + m_u32Offset;
    memmove(write_pos, buf, len);
    m_u32Offset += len;

    return true;
}

template<typename ALLOC>
bool Buffer<ALLOC>::ReallocBuffer(uint32_t len) {
    D_Assert(len > m_u32Capacity);
    D_Assert(m_pAlloc);

    uint8_t* buf = reinterpret_cast<uint8_t*>(m_pAlloc->ReallocBuf(m_pData, len));
    D_Assert(buf);
	if (buf == nullptr)
	{
		return false;
	}

	m_u32Capacity = len;
	m_pData = buf;
	return true;
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End