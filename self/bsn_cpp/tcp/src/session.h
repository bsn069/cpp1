#pragma once

#include "./main.h"
#include "./../include/i_interface.h"
#include <asio.hpp>
D_BsnNamespace1(TCP)


class C_Session 
	: public I_Session
	, public boost::enable_shared_from_this<C_Session> 
{
public:
	enum E_State
	{
		S_Close = 0,
		S_Established,
		S_Accepting,
		S_Connecting,
	};
	typedef C_Buffer<512> T_Buffer;

	asio::ip::tcp::socket	m_Socket;
	E_State volatile	m_State;
	C_DoubleList<I_Session::T_Buffers>		m_Buffers;
	T_void* m_pUserData;
	T_Buffers* m_pLastRecvBuffers;
	wstring m_wstrRemoteIP;
	T_uint16 m_u16RemotePort;

public:
	C_Session(asio::io_service& IOService);
	virtual ~C_Session();


public:
	virtual T_int32 D_const SetUserData(T_void* pUserData) override;
	virtual T_int32 D_const GetUserData(T_void*& pUserData) D_const override;

	virtual T_int32 D_const Close() override;
	virtual T_bool D_const	IsClose() override;
	virtual T_bool D_const	IsConnected() override;

	virtual T_int32 D_const Recv(T_Buffers*& pBuffers) override;
	virtual T_int32 D_const Send(T_byte* pData, T_uint32 u32Len) override;

	virtual T_int32 D_const GetRemoteIP(T_wchar D_const *& pwcIP) D_const override;
	virtual T_int32 D_const GetRemotePort(T_uint16& u16Port) D_const override;

	virtual T_int32 D_const GetLocalIP(wstring& wstrIP)  override;
	virtual T_int32 D_const GetLocalPort(T_uint16& u16Port)  override;

	E_State D_const State();
	T_void PostRead();
	T_void OnRead(I_Buffer* pData, asio::error_code D_const& error, size_t D_const bytes_transferred);
	T_void OnSend(T_byte* pData, asio::error_code D_const& error, size_t D_const bytes_transferred);
};


D_BsnNamespace1End
