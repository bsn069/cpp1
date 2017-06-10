#pragma once
#include "./../include/i_interface.h"
#include "./../include/i_log.h"


D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////
class C_Interface : public I_Interface
{
public:
	typedef std::shared_ptr<C_Interface> T_CSharePtr;
	typedef I_Log::T_SharePtr T_SharePtrLog;

public:
	virtual char const* const Name() const override;
	virtual char const* const Error(int32_t const i32ErrorCode) const override;

	virtual I_Log::T_SharePtr CreateLog(char const * const strName, void* pOwner) override;
	virtual void WaitQuit() override;

public:
	void SetLib(T_SharePtrLib lib);
	void InitLog();
	void Print(uint32_t uLogLevel, const char * strInfo);

public:
	C_Interface();
	virtual ~C_Interface();

private:
	T_SharePtrLib m_lib;
	T_SharePtrLog m_pLog;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End