#pragma once

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>

#include <memory>
 
D_BsnNamespace1(common)
//////////////////////////////////////////////////////////////////////
class I_Buffer
{
public:
	typedef std::shared_ptr<I_Buffer> T_SPI_Buffer;

public:
	virtual uint32_t 
		GetCapacity() = 0;

	virtual uint8_t* 
		GetReadPtr() = 0;
	virtual uint32_t 
		GetCanReadLength() = 0;

	virtual uint8_t* 
		GetWritePtr() = 0;
	virtual uint32_t 
		GetCanWriteLength() = 0;

	virtual bool 
		MakeCanWriteLength(uint32_t) = 0;
	virtual bool 
		Write(uint8_t const*, uint32_t) = 0;
	
	virtual bool 
		Read(uint32_t) = 0;
	virtual void 
		Write(uint32_t) = 0;

protected:
	virtual ~I_Buffer() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
