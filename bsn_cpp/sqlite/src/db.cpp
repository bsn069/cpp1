#include "db.h"

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
C_DB::Open(std::string const& strDBFile) {
	D_LogInfoF(
		m_spI_Log
		, "strDBFile=%s"
		, strDBFile.c_str()
	);

	if (m_pDB) {
		D_LogErrorF(
			m_spI_Log
			, "m_strName=%s "
			, m_strName.c_str()
		);
		return false;
	}

	auto nRet = sqlite3_open(strDBFile, &m_pDB);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "strDBFile=%s nRet=%d err=%s"
			, strDBFile.c_str()
			, nRet
			, sqlite3_errmsg(mpDB)
		);
		return false;
	}

	m_strName = strDBFile;
	setBusyTimeout(60000);
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
			, strDBFile.c_str()
			, nRet
			, sqlite3_errmsg(mpDB)
		);
		return false;
	}
	m_pDB = nullptr;
	m_strName.clear();
 
	return true;
}

string const& 
C_DB::GetName() const {
	return m_strName;
}

sqlite_int64 
C_DB::LastInsertRowId() {
	return sqlite3_last_insert_rowid(m_pDB);
}

C_Stmt* 
CreateCStmt(C_DB::T_SPC_DB spC_DB) {
	C_Stmt* imp = New<C_Stmt>(spC_DB);
	return imp;
}

void 
ReleaseCStmt(I_Stmt* iStmt) {
	C_Stmt* pImp = static_cast<C_Stmt*>(iStmt);
	Delete(pImp);
}

I_Stmt::T_SPI_Stmt
C_DB::NewStmt() {
	auto pSelfI = shared_from_this();
	auto pSelf = std::dynamic_pointer_cast<C_DB>(pSelfI);
	auto p = I_Stmt::T_SPI_Stmt(
		CreateCStmt(pSelf)
		, ReleaseCStmt
	);
	return p;
}

bool 
C_DB::Exec(char const* szSql) {
	auto nRet = sqlite3_exec(m_pDB, szSql, nullptr, nullptr, nullptr);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "strDBFile=%s nRet=%d err=%s"
			, strDBFile.c_str()
			, nRet
			, sqlite3_errmsg(mpDB)
		);
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 