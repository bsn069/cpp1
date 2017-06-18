#pragma once

namespace N_Bsn
{
	class I_Buffer
	{
	public:
		virtual uint8_t* Data() = 0;
		virtual uint32_t& Len() = 0;
		virtual uint32_t const MaxSize() const = 0;
		virtual uint32_t FreeSize() const = 0;

	public:
		virtual ~I_Buffer() = default;
	};

 
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
			u32MaxSize - m_u32Len;
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

 