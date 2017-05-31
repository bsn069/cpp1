#pragma once

#include "./main.h"
#include "./../include/i_interface.h"
#include "./session.h"
#include "./interface.h"
#include <asio.hpp>
D_BsnNamespace1(TCP)


class C_Server : public I_Server
{
public:
	typedef asio::ip::tcp::acceptor T_Acceptor;


public:
	C_Interface&				m_Interface;
	T_Acceptor					m_Accepter;
	asio::ip::tcp::endpoint*	m_pEndPoint;
	C_DoubleList<I_Session::T_Ptrs>		m_Sessions;

public:
	C_Server(C_Interface& Interface, asio::io_service& IOService);
	virtual ~C_Server() {};


public:
	virtual T_int32 D_const Bind(
		T_wchar D_const * D_const	pwcIP
		, T_uint16 D_const			u16Port
		) override;
	virtual T_int32 D_const Listen() override;
	virtual T_int32 D_const StopListen() override;
	virtual T_int32 D_const	GetSessions(I_Session::T_Ptrs*& pSessions) override;

	T_bool D_const IsBind() D_const{return (T_nullptr != m_pEndPoint); };
	T_bool D_const IsListen() D_const{return m_Accepter.is_open(); };
	T_int32 D_const Stop();

	T_void OnAccept(I_Session::T_Ptr D_const& Session, asio::error_code D_const& error);
	T_void Accept();
};


D_BsnNamespace1End
