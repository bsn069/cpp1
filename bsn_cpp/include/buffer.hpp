#pragma once

namespace N_Bsn
{
template<uint32_t u32MaxSize>
class C_Buffer : public I_Buffer
{
public:


public:
	virtual uint8_t* Data() override {return m_pData;};
	virtual uint32_t& Len() override {return m_u32Len;};
	virtual uint32_t const MaxSize() const override {return u32MaxSize;};
	virtual uint32_t FreeSize() const override 
	{
		MaxSize() - Len();
	}

	virtual uint32_t Push(uint8_t* pData, uint32_t uLen) override
	{
		uint32_t u32CanCopyLen = __min(FreeSize(), uLen);
		CopyMemory(Data() + Len(), pData, u32CanCopyLen);
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

 