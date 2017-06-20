#pragma once

namespace N_Bsn
{
	class I_Buffer
	{
	public:
		virtual uint8_t* Data() const = 0;
		virtual uint32_t& Len() = 0;
		virtual uint32_t const MaxSize() const = 0;
		// ret left can write length
		virtual uint32_t FreeSize() const = 0;
		// ret write length
		virtual uint32_t Push(uint8_t* pData, uint32_t uLen);
		bool Full() const {
			return FreeSize() == 0;
		};

	public:
		virtual ~I_Buffer() = default;
	};
} // end namespace NBSN

 