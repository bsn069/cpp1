#include "db.h"
#include "stmt.h"

#include <bsn_cpp/log/include/d_log.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

C_DB::C_DB() {

}

C_DB::~C_DB() {
	if (m_pDB != nullptr) {
		Close();
	}

	m_spI_Lib = nullptr;
	m_spI_Log = nullptr;
}


bool 
C_DB::Open(
	char const* szDBFile
	, E_OpenType eOpenType
) {
	auto sqliteOpenType = GetSqliteOpenType(eOpenType);
	D_LogInfoF(
		m_spI_Log
		, "szDBFile=%s eOpenType=%d sqliteOpenType=%d"
		, szDBFile
		, eOpenType
		, sqliteOpenType
	);

	if (m_pDB) {
		D_LogErrorF(
			m_spI_Log
			, "had open m_strDBFileName=%s "
			, m_strDBFileName.c_str()
		);
		return false;
	}

	auto nRet = sqlite3_open_v2(
		szDBFile
		, &m_pDB
		, sqliteOpenType
		, nullptr
	);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "szDBFile=%s nRet=%d err=%s"
			, szDBFile
			, nRet
			, sqlite3_errmsg(m_pDB)
		);
		sqlite3_close(m_pDB); 
		return false;
	}

	m_strDBFileName = szDBFile;
	return true;
}

bool 
C_DB::Close() {
	if (m_pDB == nullptr) {
		D_LogError(
			m_spI_Log
			, "not open db"
		);
		return false;
	}

	auto nRet = sqlite3_close(m_pDB);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "strDBFile=%s nRet=%d err=%s"
			, m_strDBFileName.c_str()
			, nRet
			, sqlite3_errmsg(m_pDB)
		);
		return false;
	}
	m_pDB = nullptr;
	m_strDBFileName.clear();
 
	return true;
}

std::string const& 
C_DB::GetName() const {
	return m_strDBFileName;
}

uint64_t 
C_DB::LastInsertRowId() {
	return (uint64_t)sqlite3_last_insert_rowid(m_pDB);
}

I_Stmt::T_SPI_Stmt
C_DB::NewStmt() {
	auto spC_DB = GetSPC_DB();
	return C_Stmt::NewI_Stmt(spC_DB);
}

C_DB::T_SPC_DB
C_DB::GetSPC_DB() {
	auto spI_DB = GetSPI_DB();
	auto spC_DB = std::dynamic_pointer_cast<C_DB>(spI_DB);
 	return spC_DB;
}

C_DB::T_SPI_DB
C_DB::GetSPI_DB() {
	return shared_from_this();
}

int 
C_DB::Exec(char const* szSql) {
	auto nRet = sqlite3_exec(
		m_pDB
		, szSql
		, nullptr
		, nullptr
		, nullptr
	);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "m_strDBFileName=%s nRet=%d err=%s"
			, m_strDBFileName.c_str()
			, nRet
			, sqlite3_errmsg(m_pDB)
		);
		return -1;
	}
	return EffectRow();
}

// I_Column
// C_DB::ExecAndGet(char const* szSql) {

// }

int 
C_DB::EffectRow() {
	return sqlite3_changes(m_pDB);
}

uint64_t 
C_DB::TotalEffectRow() {
	return sqlite3_total_changes(m_pDB);
}	

int 
C_DB::GetErrCode() {
	return sqlite3_errcode(m_pDB);
}

int 
C_DB::GetExErrCode() {
	return sqlite3_extended_errcode(m_pDB);
}

char const* 
C_DB::GetErrMsg() {
	return sqlite3_errmsg(m_pDB);
}


int
C_DB::GetSqliteOpenType(E_OpenType eOpenType) {
	static int sOpenType[E_OpenType_Count] = {
		SQLITE_OPEN_READONLY,
		SQLITE_OPEN_READWRITE,
		SQLITE_OPEN_CREATE,
		SQLITE_OPEN_URI,
		SQLITE_OPEN_MEMORY,
	};
	return sOpenType[eOpenType];
}

char const*
C_DB::Ver() const {
	return SQLITE_VERSION;
}

int
C_DB::VerNum() const {
	return SQLITE_VERSION_NUMBER;
}

char const*
C_DB::SourceId() const {
	return SQLITE_SOURCE_ID;
}

char const*
C_DB::LibVer() const {
	return sqlite3_libversion();
}

int
C_DB::LibVerNum() const {
	return sqlite3_libversion_number();
}

char const*
C_DB::LibSourceId() const {
	return sqlite3_sourceid();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 