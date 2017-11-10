#pragma once
#include "./../include/i_interface.h"
#include "net.h"
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////

class C_Interface : public I_Interface
{
public:
	typedef std::shared_ptr<C_Interface> T_CSharePtr;
	typedef C_Net::T_SharePtrCNet T_SharePtrCNet;

public:
	virtual char const* const Name() const override;
	virtual char const* const Error(int32_t const i32ErrorCode) const override;

	virtual void 	SetLog(T_SharePtrLog pLog) override {
		m_pLog = pLog;
	};
	virtual void 	WaitQuit() override{};

	virtual T_SharePtrINet Create() override;
	virtual void Release(T_SharePtrINet pINet) override;

public:
	void SetLib(T_SharePtrLib lib);


public:
	C_Interface();
	virtual ~C_Interface();

private:
	T_SharePtrLib m_lib;
	T_SharePtrLog m_pLog;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End