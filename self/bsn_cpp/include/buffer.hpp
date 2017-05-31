#pragma once

namespace N_Bsn
{
	class I_Buffer
	{
	public:
		virtual T_byte* Data() = 0;
		virtual T_uint32& Len() = 0;
		virtual T_uint32 D_const MaxSize() D_const = 0;

	public:
		virtual ~I_Buffer() = default;
	};

 
	template<T_uint32 u32MaxSize>
	class C_Buffer : public I_Buffer
	{
	public:


	public:
		virtual T_byte* Data() override {return m_pData;};
		virtual T_uint32& Len() override {return m_u32Len;};
		virtual T_uint32 D_const MaxSize() D_const override {return u32MaxSize;};


	public:
		T_uint32	m_u32Len;
		T_byte		m_pData[u32MaxSize];


	public:
		C_Buffer()
			: m_u32Len( 0 )
		{
		}
		virtual ~C_Buffer() = default;
	};

} // end namespace NBSN

 