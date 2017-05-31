#pragma once

#include "./main.h"
#include "./../include/i_interface.h"
#include "./interface.h"
D_BsnNamespace1(TCP)


class C_Client : public I_Client
{
public:
	C_Interface&	m_Interface;
	C_DoubleList<I_Session::T_Ptrs>		m_Sessions;


public:
	C_Client(C_Interface& Interface);
	virtual ~C_Client();


public:
	virtual T_int32 D_const Connect(
		T_wchar D_const * D_const	pwcIP
		, T_uint16 D_const			u16Port
		, T_void*					pUserData
		) override;
	virtual T_int32 D_const	GetSessions(I_Session::T_Ptrs*& pSessions) override;

	T_void OnConnect(I_Session::T_Ptr D_const& Session, asio::error_code D_const& error);
};


D_BsnNamespace1End
