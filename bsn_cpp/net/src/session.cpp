#include "session.h"
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include <boost/bind.hpp>
using namespace asio;
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
C_Session::C_Session(asio::io_service& IOService)
: m_Socket(IOService)
{
	m_eState.store(E_State_Close);
	m_bSending.store(false);
	m_bReading.store(false);
}


C_Session::~C_Session()
{
 
}

C_Session::E_State C_Session::State() 
{
	return (E_State)m_eState.load();
}


bool C_Session::Send(uint8_t* pData, uint32_t uLen) 
{
	// uint8_t* pSendBuff;
	// uint32_t uLen = 0;
	// m_SendRingBuffer.GetNextWriteData(pSendBuff, uLen);
	// if (uLen == 0) // no buff
	// {
	// 	m_bSending.store(false);
	// 	return false;
	// }

	// while (uLen > 0)
	// {
	// 	if (m_pSendBuffer ==  nullptr)
	// 	{
	// 		m_pSendBuffer = New<C_Buffer<2048>>();
	// 	}

	// 	auto writeLength = m_pSendBuffer->Push(pData, uLen);
	// 	uLen -= writeLength;
	// 	pData += writeLength;

	// 	if (m_pSendBuffer->Full()) // buff full
	// 	{
	// 		if (SendEnd()) 
	// 		{
	// 			return false;
	// 		}
	// 	}
	// }
	return true;
}


bool C_Session::SendEnd()
{
	// if (m_pSendBuffer == nullptr)
	// {
	// 	return false;
	// }

	// auto pSelfI = shared_from_this();
	// auto pSelf = std::dynamic_pointer_cast<C_Session>(pSelfI);

	// asio::async_write(
	// 	m_Socket 
	// 	, asio::buffer(m_pSendBuffer->Data(), m_pSendBuffer->Len())
	// 	, boost::bind(&C_Session::OnSend, pSelf, m_pSendBuffer, asio::placeholders::error, asio::placeholders::bytes_transferred)
	// );
	// m_pSendBuffer = nullptr;
	return false;
}


void C_Session::OnSend(asio::error_code const& error, size_t const bytes)
{
	if (error)
	{
		m_eState.store(E_State_Close);
		return;
	}
}

bool C_Session::Read()
{
	bool bOldValue = false;
	if (!m_bReading.compare_exchange_strong(bOldValue, true)) // 设置为读取中
	{
		return false;
	}

	uint8_t* pReadBuff;
	uint32_t uLen = 0;
	m_ReadRingBuffer.GetNextWriteData(pReadBuff, uLen);
	if (uLen == 0) // no buff
	{
		m_bReading.store(false);
		return false;
	}

	auto pSelfI = shared_from_this();
	auto pSelf = std::dynamic_pointer_cast<C_Session>(pSelfI);
	asio::async_read(
		m_Socket
		, asio::buffer(pReadBuff, uLen)
		, asio::transfer_at_least(1)
		, boost::bind(&C_Session::OnRead, pSelf, asio::placeholders::error, asio::placeholders::bytes_transferred)
	);
	return true;
}


void C_Session::OnRead(asio::error_code const& error, size_t const bytes)
{
	if (error)
	{
		m_eState.store(E_State_Close);
		return;
	}

	m_ReadRingBuffer.IncWriteDataLength(bytes);
	bool bOldValue = true;
	if (m_bReading.compare_exchange_strong(bOldValue, false)) // 设置为未读取
	{
		Read();
	}
}


bool C_Session::Recv(T_RecvBuffers& buffers)
{
	return true;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
