#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <iostream>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

class I_Column : public std::enable_shared_from_this<I_Column>{
public:
 	typedef std::shared_ptr<I_Column> T_SPI_Column;
	enum E_DataType {
		E_DataType_Int = 0,
		E_DataType_Float,
		E_DataType_Blob,
		E_DataType_Text,
		E_DataType_Null,
		E_DataType_Count,
	};

public:
	// Return a pointer to the named assigned to this result column (potentially aliased)
	virtual char const* 
		GetName() const = 0;
	// Return the number of bytes used by the text (or blob) value of the column
	virtual int 
		Size() const = 0;
	virtual int 
		Index() const = 0;

	virtual char const* 
		GetDeclType() const = 0;
	virtual E_DataType 
		GetDataType() const = 0;

	// Return the integer value of the column
	virtual int32_t 
		GetInt32() const = 0;
	virtual int64_t 
		GetInt64() const = 0;
	virtual double 
		GetDouble() const = 0;
 	virtual char const* 
		GetText() const = 0;
 	virtual std::string 
		GetString() const = 0;
 	virtual uint8_t const* 
		GetBlob() const = 0;

protected:
	virtual ~I_Column() = default;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End