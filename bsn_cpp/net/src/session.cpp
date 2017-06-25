#include "session.h"
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

using namespace asio;
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
C_Session::C_Session(asio::io_service& IOService)
: m_eState(E_State_Close)
, m_pSendBuffer(nullptr)
, m_pRecvBuffer(nullptr)
, m_Socket(IOService)
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

C_Session::E_State C_Session::State() 
{
	return m_eState;
	// return (E_State)InterlockedExchangeAdd((E_State volatile*)&m_eState, 0);
}


bool C_Session::Send(uint8_t* pData, uint32_t uLen) 
{
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

	auto pSelfI = shared_from_this();
	auto pSelf = std::dynamic_pointer_cast<C_Session>(pSelfI);

	// asio::async_write(
	// 	m_Socket 
	// 	, asio::buffer(m_pSendBuffer->Data(), m_pSendBuffer->Len())
	// 	, std::bind(&C_Session::OnSend, pSelf, m_pSendBuffer, asio::placeholders::error, asio::placeholders::bytes_transferred)
	// );
	m_pSendBuffer = nullptr;
	return false;
}


void C_Session::OnSend(I_Buffer* pSendBuffer, asio::error_code const& error, size_t const bytes)
{
	Delete(pSendBuffer);
	if (error)
	{
		// InterlockedExchange((E_State volatile*)&m_eState, E_State_Close);
		m_eState = E_State_Close;
	}
}

bool C_Session::Read()
{
		auto pSelfI = shared_from_this();
	auto pSelf = std::dynamic_pointer_cast<C_Session>(pSelfI);

	// asio::async_read(
	// 	m_Socket
	// 	, asio::buffer(m_pRecvBuffer->Data(), m_pRecvBuffer->MaxSize())
	// 	, asio::transfer_at_least(1)
	// 	, std::bind(&C_Session::OnRead, pSelf, m_pRecvBuffer, asio::placeholders::error, asio::placeholders::bytes_transferred)
	// );
	return false;
}


void C_Session::OnRead(I_Buffer* pReadBuffer, asio::error_code const& error, size_t const bytes)
{
	if (error)
	{
		// Delete(pReadBuffer);
		// InterlockedExchange((E_State volatile*)&m_eState, E_State_Close);
		m_eState = E_State_Close;
		return;
	}

	pReadBuffer->Len() = bytes;
	m_RecvBuffers.push_back(pReadBuffer);
	Read();
}


bool C_Session::Recv(T_RecvBuffers& buffers)
{
	for (auto i : m_RecvBuffers)
	{
		buffers.push_back(i);
	}
	m_RecvBuffers.clear();
	return true;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
