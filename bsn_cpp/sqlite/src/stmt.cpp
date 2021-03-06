#include "stmt.h"
#include "db.h"
#include "column.h"

#include <bsn_cpp/log/include/d_log.h>
 
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

C_Stmt::C_Stmt(C_DB::T_SPC_DB& spC_DB)
	: m_spC_DB(spC_DB)
	, m_Query(this) 
	, m_pStmt(nullptr)
{

}

C_Stmt::~C_Stmt() {
	if (m_pStmt != nullptr) {
		Finalize();
		m_pStmt = nullptr;
	}
}

bool 
C_Stmt::BindNull(int iIndex) {
	D_LogInfoF(
		m_spC_DB->m_spI_Log
		, "db=%s sql=%s iIndex=%d"
		, m_spC_DB->m_strDBFileName.c_str()
		, m_strSql.c_str()
		, iIndex
	);

 	auto nRet = sqlite3_bind_null(
		 m_pStmt
		 , iIndex
	);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spC_DB->m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strDBFileName.c_str()
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
		m_spC_DB->m_spI_Log
		, "db=%s sql=%s iIndex=%d value=%p u32Len=%u"
		, m_spC_DB->m_strDBFileName.c_str()
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
			m_spC_DB->m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strDBFileName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}

	return true;
}

bool 
C_Stmt::BindString(int iIndex, std::string& value) {
	D_LogInfoF(
		m_spC_DB->m_spI_Log
		, "db=%s sql=%s iIndex=%d value=%s"
		, m_spC_DB->m_strDBFileName.c_str()
		, m_strSql.c_str()
		, iIndex
		, value.c_str()
	);

 	auto nRet = sqlite3_bind_text(
		 m_pStmt
		 , iIndex
		 , value.c_str()
		 , static_cast<int>(value.size())
		 , SQLITE_TRANSIENT
	);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spC_DB->m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strDBFileName.c_str()
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
		m_spC_DB->m_spI_Log
		, "db=%s sql=%s iIndex=%d value=%s"
		, m_spC_DB->m_strDBFileName.c_str()
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
			m_spC_DB->m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strDBFileName.c_str()
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
		m_spC_DB->m_spI_Log
		, "db=%s sql=%s iIndex=%d value=%f"
		, m_spC_DB->m_strDBFileName.c_str()
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
			m_spC_DB->m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strDBFileName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}

	return true;
}

bool 
C_Stmt::BindInt64(int iIndex, int64_t value) {
	D_LogInfoF(
		m_spC_DB->m_spI_Log
		, "db=%s sql=%s iIndex=%d value=%d"
		, m_spC_DB->m_strDBFileName.c_str()
		, m_strSql.c_str()
		, iIndex
		, value
	);

 	auto nRet = sqlite3_bind_int64(
		 m_pStmt
		 , iIndex
		 , value
	);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spC_DB->m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strDBFileName.c_str()
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
		m_spC_DB->m_spI_Log
		, "db=%s sql=%s iIndex=%d value=%d"
		, m_spC_DB->m_strDBFileName.c_str()
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
			m_spC_DB->m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strDBFileName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}

	return true;
}


bool
C_Stmt::Step() {
	int nRet = -1;
	uint32_t u32RetryCount = 0;
	do { 
		if (nRet == SQLITE_SCHEMA) {
			Finalize();
			Compile();
		}

		nRet = sqlite3_step(m_pStmt);
		if (nRet != SQLITE_OK) {
			D_LogErrorF(
				m_spC_DB->m_spI_Log
				, "db=%s sql=%s nRet=%d err=%s"
				, m_spC_DB->m_strDBFileName.c_str()
				, m_strSql.c_str()
				, nRet
				, sqlite3_errmsg(m_spC_DB->m_pDB)
			);
			return false;
		}

		if (nRet == SQLITE_DONE) {
			m_Query.m_bEof = true;
			return true;
		} else if (nRet == SQLITE_ROW) {
			m_Query.m_bEof = false;			
			return true;
		} else {
			D_LogErrorF(
				m_spC_DB->m_spI_Log
				, "db=%s sql=%s nRet=%d err=%s"
				, m_spC_DB->m_strDBFileName.c_str()
				, m_strSql.c_str()
				, nRet
				, sqlite3_errmsg(m_spC_DB->m_pDB)
			);
		}
		++u32RetryCount;
	} while(nRet == SQLITE_SCHEMA && u32RetryCount < 10); 

	return false;
}

bool
C_Stmt::Reset() {
	auto nRet = sqlite3_reset(m_pStmt);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spC_DB->m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strDBFileName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}
	m_Query.OnReset();
	return true;
}

bool
C_Stmt::Compile(char const* strSql) {
	Finalize();
	m_strSql = strSql;
	return Compile();
}

bool 
C_Stmt::Finalize() {
	auto nRet = sqlite3_finalize(m_pStmt);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spC_DB->m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strDBFileName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}
	m_pStmt = nullptr;
	m_Query.OnFinalize();
	return true;
}

bool
C_Stmt::Compile() {	
	auto nRet = sqlite3_prepare_v3(
		m_spC_DB->m_pDB
		, m_strSql.c_str()
		, -1
		, 0
		, &m_pStmt
		, nullptr
	);
	if (nRet != SQLITE_OK) {
		D_LogErrorF(
			m_spC_DB->m_spI_Log
			, "db=%s sql=%s nRet=%d err=%s"
			, m_spC_DB->m_strDBFileName.c_str()
			, m_strSql.c_str()
			, nRet
			, sqlite3_errmsg(m_spC_DB->m_pDB)
		);
		return false;
	}
	m_Query.OnCompile();
	return true;
}

I_Query* 
C_Stmt::Query() {
	return &m_Query;
}



bool 
C_Stmt::Bind(int iIndex, int value) {
	return BindInt(iIndex, value);
}

bool 
C_Stmt::Bind(int iIndex, int64_t value) {
	return BindInt64(iIndex, value);
}

bool 
C_Stmt::Bind(int iIndex, double value) {
	return BindDouble(iIndex, value);
}

bool 
C_Stmt::Bind(int iIndex) {
	return BindNull(iIndex);
}

bool 
C_Stmt::Bind(int iIndex, std::string& value) {
	return BindString(iIndex, value);	
}

bool 
C_Stmt::Bind(int iIndex, char const* value) {
	return BindText(iIndex, value);
}

bool 
C_Stmt::Bind(int iIndex, uint8_t const* value,uint32_t u32Len) {
	return BindBlob(iIndex, value, u32Len);
}

C_ColumnEx
C_Stmt::GetC_ColumnEx(int iIndex) {
	auto spC_Stmt = GetSPC_Stmt();
	auto spI_Column = C_Column::NewI_Column(spC_Stmt, iIndex);
 	return C_ColumnEx(spI_Column);
}

C_Stmt::T_SPC_Stmt
C_Stmt::GetSPC_Stmt() {
	auto spI_Stmt = shared_from_this();
	auto spC_Stmt = std::dynamic_pointer_cast<C_Stmt>(spI_Stmt);
 	return spC_Stmt;
}

C_Stmt::T_SPI_Stmt
C_Stmt::GetSPI_Stmt() {
	return shared_from_this();
}


C_Stmt* 
CreateCStmt(C_DB::T_SPC_DB& spC_DB) {
	C_Stmt* imp = New<C_Stmt>(spC_DB);
	return imp;
}

void 
ReleaseCStmt(I_Stmt* iStmt) {
	C_Stmt* pImp = static_cast<C_Stmt*>(iStmt);
	Delete(pImp);
}

C_Stmt::T_SPC_Stmt
C_Stmt::NewC_Stmt(C_DB::T_SPC_DB& spC_DB) {
	auto spC_Stmt = C_Stmt::T_SPC_Stmt(
		CreateCStmt(spC_DB)
		, ReleaseCStmt
	);
	return spC_Stmt;
}

C_Stmt::T_SPI_Stmt
C_Stmt::NewI_Stmt(C_DB::T_SPC_DB& spC_DB) {
	auto spC_Stmt = C_Stmt::NewC_Stmt(spC_DB);
	return spC_Stmt->shared_from_this();
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 