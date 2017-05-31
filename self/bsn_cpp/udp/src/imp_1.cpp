#include "./main.h"
#ifdef D_USE_1

#include <asio.hpp>
D_BsnNamespace1(UDP)
//////////////////////////////////////////////////////////////////////

using asio::ip::udp;
using asio::io_service;
using asio::ip::address;
using D_N2(Common, String)::Unicode2ANSI;

class C_Imp : public I_Interface
{

public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;

	virtual T_int32 D_const	Bind(
		T_wchar D_const * D_const	pwcIP
		, T_uint16 D_const			u16Port
		) override;
	virtual T_int32 D_const	Recv(
		T_byte *  					pbyData
		, T_uint32 D_const			u32Len
		, std::size_t&				stLen
		) override;
	virtual T_int32 D_const	Send(
		T_byte D_const * D_const	pbyData
		, T_uint32 D_const			u32Len
		, std::size_t& stLen
		) override;
	virtual T_int32 D_const	SetSendAddr(
		T_wchar D_const * D_const	pwcIP
		, T_uint16 D_const			u16Port
		) override;

public:
	io_service		m_IOService;
	udp::socket*	m_pSocket;
	udp::endpoint	m_EndPoint;
	udp::endpoint	m_DesEndPoint;


public:
	C_Imp();
	virtual ~C_Imp();

private:

};


D_FunImp D_BSN_udp_DLL I_Interface* Create()
{
	C_Imp* imp = New<C_Imp>();
	return imp;
}

C_Imp::C_Imp()
	: m_pSocket( T_nullptr )
{
}

C_Imp::~C_Imp()
{
	Delete(m_pSocket);
}


T_wchar D_const * D_const  C_Imp::Name() D_const
{
	return L"C_Imp";
}


T_wchar D_const * D_const C_Imp::Error(T_int32 D_const i32ErrorCode) D_const
{
	switch ( i32ErrorCode )
	{
	case -1: return L"had init";
	case -2: return L"not init";
	default: return L"Unknown";
	}
}



T_int32 D_const	C_Imp::Bind(
	T_wchar D_const * D_const	pwcIP
	, T_uint16 D_const			u16Port
	)
{
	if (T_nullptr != m_pSocket)
	{
		return -1;
	}

	if (T_nullptr == pwcIP)
	{
		m_EndPoint = udp::endpoint(udp::v4(), u16Port);
	}
	else
	{
		string strIP;
		Unicode2ANSI(pwcIP, strIP);
		address addr = address::from_string(strIP);
		m_EndPoint = udp::endpoint(addr, u16Port);
	}
	m_pSocket = New<udp::socket>(m_IOService, m_EndPoint);
	return 0;
}

T_int32 D_const	C_Imp::Recv(
	T_byte * pbyData
	, T_uint32 D_const			u32Len
	, std::size_t& stLen
	)
{
	if (T_nullptr == m_pSocket)
	{
		return -2;
	}

	asio::error_code ec;
	stLen = m_pSocket->receive_from(
		asio::buffer(pbyData, u32Len)
		, m_DesEndPoint
		, 0
		, ec
		);

	return 0;
}


T_int32 D_const	C_Imp::Send(
	T_byte D_const * D_const	pbyData
	, T_uint32 D_const			u32Len
	, std::size_t& stLen
	)
{
	if (T_nullptr == m_pSocket)
	{
		return -2;
	}

	asio::error_code ec;
	stLen = m_pSocket->send_to(
		asio::buffer(pbyData, u32Len)
		, m_DesEndPoint
		, 0
		, ec
		);

	return 0;
}



T_int32 D_const C_Imp::SetSendAddr(
	T_wchar D_const * D_const	pwcIP
	, T_uint16 D_const		u16Port
	)
{
	string strIP;
	if (T_nullptr == pwcIP)
	{
		strIP = "127.0.0.1";
	}
	else
	{
		Unicode2ANSI(pwcIP, strIP);
	}
	address addr = address::from_string(strIP);
	m_DesEndPoint = udp::endpoint(addr, u16Port);

	return 0;
}








D_BsnNamespace1End
#endif