#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <iostream>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

class I_Column {
public:
 	typedef std::shared_ptr<I_Column> T_SPI_Column;

public:
	virtual char const* 
		GetName() = 0;
	virtual int 
		GetType() = 0;

	virtual int 
		GetInt() = 0;
	virtual int64_t 
		GetInt64() = 0;
	virtual double 
		GetDouble() = 0;
 	virtual char const* 
		GetText(char const* defaultValue = "") = 0;
 	virtual std::string 
		GetString() = 0;
 	virtual uint8_t const* 
		GetBlob() = 0;

	// Return the number of bytes used by the text (or blob) value of the column
	virtual int 
		Size() = 0;

    inline operator int() const {
        return getInt();
    }
protected:
	virtual ~I_Column() = default;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End