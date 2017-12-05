#include "query.h"
#include "stmt.h"
#include "db.h"

#include <bsn_cpp/log/include/d_log.h>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

C_Query::C_Query(C_Stmt& stmt)
	: m_Stmt(stmt) {
	Clear();
}

C_Query::~C_Query() {

}



char const*
C_Query::ColumnName(int nColumn) {
	return sqlite3_column_name(m_Stmt.m_pStmt, nColumn);
}


int 
C_Query::ColumnIndex(char const* strColumnName) {
	for (int iIndex = 0; iIndex < ColumnCount(); ++iIndex) {
		auto name = ColumnName(iIndex);
		if (StrCmp(name, strColumnName) == 0) {
			return iIndex;
		}
	}
	return -1;
}

char const*
C_Query::ColumnDeclType(int nColumn) {
	return sqlite3_column_decltype(m_Stmt.m_pStmt, nColumn);
}

int
C_Query::ColumnDataType(int nColumn) {
	return sqlite3_column_type(m_Stmt.m_pStmt, nColumn);
}

bool 
C_Query::ColumnIsNull(int nColumn) {
	return (ColumnDataType(nColumn) == SQLITE_NULL);
}

bool 
C_Query::ColumnIsNull(char const* strColumnName) {
	auto nColumn = ColumnIndex(strColumnName);
	return (ColumnDataType(nColumn) == SQLITE_NULL);
}

const uint8_t* 
C_Query::GetBlob(int nColumn, int& nLen) {
	nLen = sqlite3_column_bytes(m_Stmt.m_pStmt, nColumn);
	return (const uint8_t*)sqlite3_column_blob(m_Stmt.m_pStmt, nColumn);
}

const uint8_t* 
C_Query::GetBlob(char const* strColumnName, int& nLen) {
	auto nColumn = ColumnIndex(strColumnName);
	return GetBlob(nColumn, nLen);
}

const char* 
C_Query::GetText(int nColumn, char const* strNullValue) {
	if (ColumnDataType(nColumn) == SQLITE_NULL) {
		return szNullValue;
	}
	return (const char*)sqlite3_column_text(m_Stmt.m_pStmt, nColumn);
}

const char* 
C_Query::GetText(char const* strColumnName, char const* strNullValue) {
	auto nColumn = ColumnIndex(strColumnName);
	return GetText(nColumn, strNullValue);
}

double 
C_Query::GetDouble(int nColumn, double dNullValue) {
	if (ColumnDataType(nColumn) == SQLITE_NULL) {
		return dNullValue;
	}
	return (double)sqlite3_column_double(m_Stmt.m_pStmt, nColumn);
}

double 
C_Query::GetDouble(char const* strColumnName, double dNullValue) {
	auto nColumn = ColumnIndex(strColumnName);
	return GetDouble(nColumn, dNullValue);
}

int 
C_Query::GetInt(int nColumn, int iNullValue) {
	if (ColumnDataType(nColumn) == SQLITE_NULL) {
		return iNullValue;
	}
	return (int)sqlite3_column_int(m_Stmt.m_pStmt, nColumn);
}

int 
C_Query::GetInt(char const* strColumnName, int iNullValue) {
	auto nColumn = ColumnIndex(strColumnName);
	return GetInt(nColumn, iNullValue);
}


void
C_Query::OnCompile() {
	Clear();
}

int 
C_Query::ColumnCount() {
	return sqlite3_column_count(m_Stmt.m_pStmt);
}

void
C_Query::OnReset() {
	Clear();
}

void
C_Query::OnFinalize() {
	Clear();
}

void
C_Query::Clear() {
	m_bEof = false;
	m_nEffectRow = -1;
}

bool 
C_Query::FetchRow() {
	if (Eof()) {
		return false;
	}
	return m_Stmt.Step();
}

bool 
C_Query::Eof() {
	return m_bEof;
}

int 
C_Query::EffectRow() {
	if (m_nEffectRow == -1) {
		m_nEffectRow = sqlite3_changes(m_Stmt.m_pStmt);
	}
	return m_nEffectRow;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 