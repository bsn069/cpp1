#pragma once

#include "i_buffer.hpp"
#include <algorithm>
#include <cstring>

namespace N_Bsn
{
template<uint32_t u32MaxSize>
class C_Buffer : public I_Buffer
{
public:


public:
	virtual uint8_t const * Data() const override {return m_pData;};
	virtual uint32_t& Len() override {return m_u32Len;};
	virtual uint32_t const MaxSize() const override {return u32MaxSize;};
	virtual uint32_t FreeSize() const override 
	{
		return MaxSize() - m_u32Len;
	}

	virtual uint32_t Push(uint8_t* pData, uint32_t uLen) override
	{
		uint32_t u32CanCopyLen = std::min(FreeSize(), uLen);
		memcpy(m_pData + Len(), pData, u32CanCopyLen);
		Len() += u32CanCopyLen;
		return u32CanCopyLen;
	}

public:
	uint32_t	m_u32Len;
	uint8_t		m_pData[u32MaxSize];


public:
	C_Buffer()
		: m_u32Len( 0 )
	{
	}
	virtual ~C_Buffer() = default;
};

} // end namespace NBSN

 