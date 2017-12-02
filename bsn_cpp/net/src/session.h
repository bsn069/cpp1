#pragma once
#include "./../include/i_session.h"

#include <bsn_cpp/common/include/i_common.h>

#include <boost/asio.hpp>
#include <atomic>
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////

class C_Session : public I_Session
{
public:
	typedef std::shared_ptr<C_Session> T_SPC_Session;

public:
	virtual I_Session::E_State 
		GetState() const override {
			return m_eState;
		};
	virtual bool 
		Send(uint8_t const* pData, uint32_t u32Len) override;
	virtual void 
		Close() override;

public:
	boost::asio::ip::tcp::socket& 
		GetSocket() {
			return m_Socket;
		};
	
	void 
		OnSend(boost::system::error_code const&, size_t const);
	bool 
		IsWork(); 
	bool 
		CommitSendData();

public:
	C_Session(boost::asio::io_service&, D_N1(common)::I_Common::T_SPI_Common);
	virtual ~C_Session();

protected:
	boost::asio::ip::tcp::socket 	m_Socket;
	I_Session::E_State 				m_eState;
	D_N1(common)::I_Buffer::T_SPI_Buffer 	m_spI_BufferWaitSend;
	D_N1(common)::I_Buffer::T_SPI_Buffer 	m_spI_BufferSending;
	bool m_bCanCommitSendData;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End