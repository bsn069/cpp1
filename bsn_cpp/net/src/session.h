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
	virtual E_State 
		State() const override {
			return m_eState;
		};
	virtual bool 
		Send(uint8_t const* pData, uint32_t u32Len) override;
	virtual void 
		Close() override;

public:
	asio::ip::tcp::socket 
		GetSocket() {
			return m_Socket;
		};
	
	void 
		OnSend(asio::error_code const&, size_t const);
	bool 
		IsWork(); 
	bool 
		CommitSendData();

public:
	C_Session(asio::io_service&, D_N1(common)::T_SPI_Common);
	virtual ~C_Session();

protected:
	asio::ip::tcp::socket 	m_Socket;
	E_State 				m_eState;
	D_N1(common)::I_Buffer::T_SPI_Buffer 	m_spI_BufferWaitSend;
	D_N1(common)::I_Buffer::T_SPI_Buffer 	m_spI_BufferSending;
	bool m_bCanCommitSendData;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End