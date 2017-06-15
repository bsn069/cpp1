#pragma once
#include "./../include/i_interface.h"

D_BsnNamespace1(t_share)
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