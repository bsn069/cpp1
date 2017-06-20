#include "session.h"

D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
C_Session::C_Session()
: m_eState(E_State_Close)
, m_pSendBuffer(nullptr)
{
	m_pRecvBuffer = New<C_Buffer<2048>>();
}


C_Session::~C_Session()
{
	Delete(m_pSendBuffer);
	for (auto i : m_RecvBuffers)
	{
		Delete(i);
	}
}

E_State C_Session::State() 
{
	return (E_State)InterlockedExchangeAdd((E_State volatile*)&m_eState, 0);
}


bool C_Session::Send(uint8_t* pData, uint32_t uLen) 
{
	uint32_t hadCopyLen = 0;
	while (uLen > 0)
	{
		if (m_pSendBuffer ==  nullptr)
		{
			m_pSendBuffer = New<C_Buffer<2048>>();
		}

		auto writeLength = m_pSendBuffer->Push(pData, uLen);
		uLen -= writeLength;
		pData += writeLength;

		if (m_pSendBuffer->Full()) // buff full
		{
			if (SendEnd()) 
			{
				return false;
			}
		}
	}
	return true;
}


bool C_Session::SendEnd()
{
	if (m_pSendBuffer == nullptr)
	{
		return false;
	}

	asio::async_write(
		m_Socket 
		, asio::buffer(m_pSendBuffer->Data(), m_pSendBuffer->Len())
		, bind(&C_Session::OnSend, shared_from_this(), m_pSendBuffer, placeholders::error, placeholders::bytes_transferred)
	);
	m_pSendBuffer = nullptr;
	return false;
}


void C_Session::OnSend(I_Buffer* pSendBuffer, asio::error_code& error, size_t bytes)
{
	Delete(pSendBuffer);
	if (error)
	{
		InterlockedExchange((E_State volatile*)&m_eState, E_State_Close);
	}
}

bool C_Session::Read()
{
	asio::async_read(
		m_Socket
		, buffer(m_pRecvBuffer->Data(), m_pRecvBuffer->MaxSize())
		, transfer_at_least(1)
		, bind(&C_Session::OnRead, shared_from_this(), m_pRecvBuffer, placeholders::error, placeholders::bytes_transferred)
	);
	return false;
}


void C_Session::OnRead(I_Buffer* pReadBuffer, asio::error_code& error, size_t bytes)
{
	if (error)
	{
		// Delete(pReadBuffer);
		InterlockedExchange((E_State volatile*)&m_eState, E_State_Close);
		return;
	}

	pReadBuffer->Len() = bytes;
	m_RecvBuffers.push_back(pReadBuffer);
	Read();
}


void C_Session::Recv(T_RecvBuffers& buffers)
{
	for (auto i : m_RecvBuffers)
	{
		buffers.push_back(i);
	}
	m_RecvBuffers.clear();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
