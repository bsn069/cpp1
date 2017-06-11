#pragma once
#include "./../include/i_interface.h"
#include "./lib.h"
#include <map>
#include <list>
D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////
class C_Interface : public I_Interface
{
public:
	typedef std::map<std::string, I_Lib::T_SharePtr> T_Libs;
	typedef std::list<I_Lib::T_SharePtr> T_WaitDelLibs;

	
public:
	virtual I_Lib::T_SharePtr	Load(
		const char* strLibName
		, const char* strLibPath
		, const char* strDebugSuffix
		, const char* strReleaseSuffix
	) override;
	virtual I_Lib::T_SharePtr	Get(const char* strLibName) override;
	virtual void	WaitQuit() override;
	virtual void 	SetLog(T_SharePtrLog pLog) override {
		m_pLog = pLog;
	};


public:
	virtual char const* const Name() const override;
	virtual char const* const Error(int32_t const i32ErrorCode) const override;

public:
	C_Interface();
	virtual ~C_Interface();

private:
	T_Libs m_Libs;
	T_WaitDelLibs m_WaitDelLibs;
	T_SharePtrLog m_pLog;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End