#pragma once
#include "./../include/i_session.h"
#include <bsn_cpp/include/buffer.hpp>
#include <asio.hpp>
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////

class C_Session : public I_Session
{
public:
	typedef std::shared_ptr<C_Interface> T_SharePtrCSession;

public:
	virtual E_State State() override;
	virtual bool Send(uint8_t* pData, uint32_t uLen)override;
	virtual bool SendEnd() override;
	virtual void Recv(T_RecvBuffers& buffers) override;


public:
	void OnSend(I_Buffer* pSendBuffer, asio::error_code& error, size_t bytes);
	void Read();
	void OnRead(I_Buffer* pSendBuffer, asio::error_code& error, size_t bytes);

public:
	C_Session();
	virtual ~C_Session();

private:
	E_State volatile m_eState;
	I_Buffer* m_pSendBuffer;
	asio::ip::tcp::socket m_Socket;
	T_RecvBuffers m_RecvBuffers;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End