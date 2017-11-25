#pragma once
#include "./../include/i_session.h"
#include <bsn_cpp/include/buffer.hpp>
#include <bsn_cpp/include/ring_buffer.hpp>
#include <boost/asio.hpp>
#include <atomic>
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////

class C_Session : public I_Session
{
public:
	typedef std::shared_ptr<C_Session> T_SPC_Session;

public:
	virtual E_State State() const override;
	virtual bool Send(uint8_t const* pData, uint32_t uLen) override;
	virtual void Close() override;

public:
	bool PostSend();
	void OnSend(asio::error_code const& error, size_t const bytes);

	bool PostRead();
	void OnRead(asio::error_code const& error, size_t const bytes);

	void OnAccept();
	void OnConnect();


	asio::ip::tcp::socket& Socket() {
		return m_Socket;
	}

public:
	C_Session(asio::io_service& IOService);
	virtual ~C_Session();

private:
	asio::ip::tcp::socket m_Socket;

	C_RingBuffer<4096>	m_ReadRingBuffer;
	std::atomic<bool> 	m_bReading;

	C_RingBuffer<4096>	m_SendRingBuffer;
	std::atomic<bool> 	m_bSending;

	std::atomic<uint8_t> m_eState;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End