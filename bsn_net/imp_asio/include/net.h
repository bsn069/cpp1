#pragma once
#include "port.h"
#include "socket.h"
#include <asio.hpp>

class CNet
{
public:
	void	Accept(void);

	void	OnAccept(CSocket::Ptr pSocket, const asio::error_code& Error);
	void	OnConnect(CSocket::Ptr pSocket, const asio::error_code& Error);

public:
	asio::io_service 		m_IO;
	asio::io_service::work 	m_Work;
	asio::ip::tcp::acceptor m_Acceptor;
}