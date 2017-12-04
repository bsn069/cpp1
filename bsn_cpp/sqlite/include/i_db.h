#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <iostream>

D_BsnNamespace1(sqlite)
//////////////////////////////////////////////////////////////////////

class I_DB 
{
public:
	virtual bool Open(std::string& strDBFile) = 0;
	virtual bool Close() = 0;

	virtual bool ExecDML(std::string& strSql) = 0;

protected:
	virtual ~I_Log() = default;

// Operations
public:

    virtual ~CppSQLite3DB();

    void open(LPCTSTR szFile);

    void close();
    bool tableExists(LPCTSTR szTable);
    int execDML(LPCTSTR szSQL);

    CppSQLite3Query execQuery(LPCTSTR szSQL);

    int execScalar(LPCTSTR szSQL);
	CString execScalarStr(LPCTSTR szSQL);

    CppSQLite3Statement compileStatement(LPCTSTR szSQL);

    sqlite_int64 lastRowId();

    void interrupt() { sqlite3_interrupt(mpDB); }

    void setBusyTimeout(int nMillisecs);

    static const char* SQLiteVersion() { return SQLITE_VERSION; }

private:

    CppSQLite3DB(const CppSQLite3DB& db);
    CppSQLite3DB& operator=(const CppSQLite3DB& db);

    sqlite3_stmt* compile(LPCTSTR szSQL);

    void checkDB();
public:
    sqlite3* mpDB;
    int mnBusyTimeoutMs;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End