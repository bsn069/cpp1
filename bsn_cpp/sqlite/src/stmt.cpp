#include "./db.h"

#include <bsn_cpp/log/include/d_log.h>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

C_Stmt::C_Stmt() {

}

C_Stmt::~C_Stmt() {
	Finalize();
}

bool 
C_Stmt::BindNull(int iIndex) {
	D_LogInfoF(
		m_spI_Log
		, "db=%s sql=%s iIndex=%d"
		, m_spC_DB->m_strName.c_str()
		, m_strSql.c_str()
		, iIndex
	);

 	auto nRet = sqlite3_bind_null(
		 m_pStmt
		 , iIndex
	);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}

	return true;
}

bool 
C_Stmt::BindBlob(int iIndex, uint8_t const* value, uint32_t u32Len) {
	D_LogInfoF(
		m_spI_Log
		, "db=%s sql=%s iIndex=%d value=%p u32Len=%u"
		, m_spC_DB->m_strName.c_str()
		, m_strSql.c_str()
		, iIndex
		, value
		, u32Len
	);

 	auto nRet = sqlite3_bind_blob(
		 m_pStmt
		 , iIndex
		 , (const void*)value
		 , u32Len
		 , SQLITE_TRANSIENT
	);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}

	return true;
}


bool 
C_Stmt::BindText(int iIndex, char const* value) {
	D_LogInfoF(
		m_spI_Log
		, "db=%s sql=%s iIndex=%d value=%s"
		, m_spC_DB->m_strName.c_str()
		, m_strSql.c_str()
		, iIndex
		, value
	);

 	auto nRet = sqlite3_bind_text(
		 m_pStmt
		 , iIndex
		 , value
		 , -1
		 , SQLITE_TRANSIENT
	);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}

	return true;
}

bool 
C_Stmt::BindDouble(int iIndex, double value) {
	D_LogInfoF(
		m_spI_Log
		, "db=%s sql=%s iIndex=%d value=%f"
		, m_spC_DB->m_strName.c_str()
		, m_strSql.c_str()
		, iIndex
		, value
	);

 	auto nRet = sqlite3_bind_double(
		 m_pStmt
		 , iIndex
		 , value
	);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}

	return true;
}

bool 
C_Stmt::BindInt(int iIndex, int value) {
	D_LogInfoF(
		m_spI_Log
		, "db=%s sql=%s iIndex=%d value=%d"
		, m_spC_DB->m_strName.c_str()
		, m_strSql.c_str()
		, iIndex
		, value
	);

 	auto nRet = sqlite3_bind_int(
		 m_pStmt
		 , iIndex
		 , value
	);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}

	return true;
}

bool 
C_Stmt::Reset() {
	auto nRet = sqlite3_reset(m_pStmt);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}

	return true;
}

bool 
C_Stmt::Finalize() {
	auto nRet = sqlite3_finalize(m_pStmt);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}

	return true;
}

int
C_Stmt::Exec() {
	auto nRet = sqlite3_step(m_pStmt);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return -1;
	}

	if (nRet == SQLITE_DONE) {
		int nRowsChanged = sqlite3_changes(m_pStmt);
		Reset();
		return nRowsChanged;
	}


}


bool
C_Stmt::Compile() {	
	auto nRet = sqlite3_prepare(
		m_spC_DB->m_pDB
		, m_strSql.c_str()
		, -1
		, &m_pStmt
		, nullptr
	);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}
 
	return true;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 