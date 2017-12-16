#pragma once

#include "i_column.h"

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
 

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

class C_ColumnEx {
public:
	// Return a pointer to the named assigned to this result column (potentially aliased)
	inline char const* 
		Name() const {
			return m_spI_Column->GetName();
		}

	inline int 
		Index() const {
			return m_spI_Column->Index();
		}

	// Return the number of bytes used by the text (or blob) value of the column
	inline int 
		Size() const {
			return m_spI_Column->Size();
		}

	inline char const* 
		GetDeclType() const {
			return m_spI_Column->GetDeclType();
		}

	inline I_Column::E_DataType 
		GetDataType() const {
			return m_spI_Column->GetDataType();
		}

	inline bool 
		IsFloat() const {
			return (I_Column::E_DataType_Float == GetDataType());
		}

    inline bool
		IsText() const {
			return (I_Column::E_DataType_Text == GetDataType());
		}

    inline bool
		IsBlob() const {
			return (I_Column::E_DataType_Blob == GetDataType());
		}

    inline bool
		IsNull() const {
			return (I_Column::E_DataType_Null == GetDataType());
		}

    inline bool
		IsInt() const {
			return (I_Column::E_DataType_Int == GetDataType());
		}

    inline operator
		int32_t() const {
			return m_spI_Column->GetInt32();
		}

    inline operator
		uint32_t() const {
			return (uint32_t)m_spI_Column->GetInt32();
		}

	inline operator
		int64_t() const {
			return m_spI_Column->GetInt64();
		}

	inline operator
		uint64_t() const {
			return (uint64_t)m_spI_Column->GetInt64();
		}

    inline operator
		double() const {
			return m_spI_Column->GetDouble();
		}

    inline operator
		float() const {
			return (float)m_spI_Column->GetDouble();
		}

    inline operator
		char const*() const {
			return m_spI_Column->GetText();
		}

    inline operator
		std::string() const {
			return m_spI_Column->GetString();
		}

    inline operator
		uint8_t const*() const {
			return m_spI_Column->GetBlob();
		}

    inline operator
		void const*() const {
			return (void const*)m_spI_Column->GetBlob();
		}

public:
	C_ColumnEx(I_Column::T_SPI_Column& spI_Column)
	: m_spI_Column(spI_Column) {

	}

	~C_ColumnEx() {
		m_spI_Column = nullptr;
	}

private:
	I_Column::T_SPI_Column m_spI_Column;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End