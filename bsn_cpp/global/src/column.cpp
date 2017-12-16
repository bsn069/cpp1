#include "column.h"
#include "stmt.h"

#include <bsn_cpp/log/include/d_log.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <string.h>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

C_Column::C_Column(C_Stmt::T_SPC_Stmt spC_Stmt, int index)
	: m_spC_Stmt(spC_Stmt)
	, m_index(index) {

}

C_Column::~C_Column() {
	m_spC_Stmt = nullptr;
}

char const* 
C_Column::GetName() const {
	return sqlite3_column_name(Stmt(), Index());
}

char const* 
C_Column::GetDeclType() const {
	return sqlite3_column_decltype(Stmt(), Index());
}

int 
C_Column::GetRawDataType() const {
	return sqlite3_column_type(Stmt(), Index());
}

I_Column::E_DataType 
C_Column::GetDataType() const {
	static I_Column::E_DataType sDataType[E_DataType_Count] = {
		E_DataType_Int,
		E_DataType_Float,
		E_DataType_Blob,
		E_DataType_Text,
		E_DataType_Null,
	};
	return sDataType[GetRawDataType() - 1];
}


int 
C_Column::Size() const {
   return sqlite3_column_type(Stmt(), Index());
}

int 
C_Column::Index() const {
	return m_index;
}

int32_t 
C_Column::GetInt32() const {
	return (int32_t)sqlite3_column_int(Stmt(), Index());
}

int64_t 
C_Column::GetInt64() const {
	return (int64_t)sqlite3_column_int64(Stmt(), Index());
}

double 
C_Column::GetDouble() const {
	return (double)sqlite3_column_double(Stmt(), Index());
}

char const* 
C_Column::GetText()const {
	return reinterpret_cast<char const*>(sqlite3_column_text(Stmt(), Index()));
}

std::string 
C_Column::GetString() const {
 	// Note: using sqlite3_column_blob and not sqlite3_column_text
    // - no need for sqlite3_column_text to add a \0 on the end, as we're getting the bytes length directly
     char const* data = reinterpret_cast<char const *>(GetBlob());

    // SQLite docs: "The safest policy is to invoke… sqlite3_column_blob() followed by sqlite3_column_bytes()"
    // Note: std::string is ok to pass nullptr as first arg, if length is 0
    return std::string(data, sqlite3_column_bytes(Stmt(), Index()));
}

uint8_t const* 
C_Column::GetBlob() const {
	return reinterpret_cast<uint8_t const*>(sqlite3_column_blob(Stmt(), Index()));
}

sqlite3_stmt* 
C_Column::Stmt() const {
	return m_spC_Stmt->m_pStmt;
}

C_Column* 
CreateCColumn(C_Stmt::T_SPC_Stmt& spC_Stmt, int iIndex) {
	C_Column* imp = New<C_Column>(spC_Stmt, iIndex);
	return imp;
}

void 
ReleaseCColumn(I_Column* iColumn) {
	C_Column* pImp = static_cast<C_Column*>(iColumn);
	Delete(pImp);
}

C_Column::T_SPC_Column
C_Column::NewC_Column(C_Stmt::T_SPC_Stmt& spC_Stmt, int iIndex) {
	auto p = C_Column::T_SPC_Column(
		CreateCColumn(spC_Stmt, iIndex)
		, ReleaseCColumn
	);
	return p;
}

C_Column::T_SPI_Column
C_Column::NewI_Column(C_Stmt::T_SPC_Stmt& spC_Stmt, int iIndex) {
	auto spC_Column = C_Column::NewC_Column(spC_Stmt, iIndex);
	auto spI_Column = std::dynamic_pointer_cast<I_Column>(spC_Column);
	return spI_Column;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 