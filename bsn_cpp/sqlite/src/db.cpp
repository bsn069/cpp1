#include "./db.h"

#include <bsn_cpp/log/include/d_log.h>

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

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 