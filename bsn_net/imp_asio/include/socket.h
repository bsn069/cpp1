#pragma once
#include "port.h"
#include <asio.hpp>

class CSocket : public enable_shared_from_this<CSocket>, public ISocket
{
public:
	typedef shared_ptr<CSocket> T_Ptr;

	bool Send(int8_t* pData, uint32_t uLen);

public:
	asio::ip::tcp::socket	m_Socket;
	asio::ip::address		m_Local;
	asio::ip::address		m_Remote;
}