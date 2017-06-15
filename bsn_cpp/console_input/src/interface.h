#pragma once
#include "./../include/i_interface.h"
#include <thread>

D_BsnNamespace1(console_input)
//////////////////////////////////////////////////////////////////////

class C_Interface : public I_Interface
{
public:
	typedef std::shared_ptr<C_Interface> T_CSharePtr;

public:
	virtual char const* const Name() const override;
	virtual char const* const Error(int32_t const i32ErrorCode) const override;

	virtual void 	SetLog(T_SharePtrLog pLog) override {
		m_pLog = pLog;
	};
	virtual void 	Start() override;
	virtual void 	WaitQuit() override;


public:
	void SetLib(T_SharePtrLib lib);
	void ThreadInput();

public:
	C_Interface();
	virtual ~C_Interface();

private:
	T_SharePtrLib m_lib;
	T_SharePtrLog m_pLog;
	std::thread* m_pInputThread;
	bool m_bQuit;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End