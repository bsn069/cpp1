#pragma once
#include "./../include/i_session.h"
#include <bsn_cpp/include/buffer.hpp>
#include <bsn_cpp/include/ring_buffer.hpp>
#include <asio.hpp>
#include <atomic>
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////

class C_Net : public I_Net
{
public:
	typedef C_Session::T_SharePtrCSession T_SharePtrCSession;
public:


public:
	void Listen(std::string strIp, uint8_t uPort);
	void Connect(std::string strIp, uint8_t uPort);
 
	void PostAccept();
	void OnAccept(T_SharePtrCSession Session, const error_code& Error);
public:
	C_Net();
	virtual ~C_Net();

private:
	asio::io_service		m_IO;
	asio::io_service::work	m_Work;
	asio::ip::tcp::acceptor	m_Acceptor;

	std::list<T_SharePtrCSession> m_Accepts;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End