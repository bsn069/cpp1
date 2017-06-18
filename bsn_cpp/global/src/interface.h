#pragma once
#include "./../include/i_interface.h"

D_BsnNamespace1(global)
//////////////////////////////////////////////////////////////////////

class C_Interface : public I_Interface
{
public:
	typedef std::shared_ptr<C_Interface> T_CSharePtr;

public:
	virtual char const* const Name() const override;
	virtual char const* const Error(int32_t const i32ErrorCode) const override;

	virtual void Start(int argc, char* argv[]) override;


public:
	void Loop();
	void WaitQuit();

public:
	C_Interface();
	virtual ~C_Interface();

private:
	bool m_bRun;
	T_SharePtrLog m_pLog;
	T_SharePtrLibLoader m_pLibLoader;
	T_SharePtrLogInterace m_pLogInterface;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End