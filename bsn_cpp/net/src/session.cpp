#include "session.h"
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include <boost/bind.hpp>
using namespace boost::asio;
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
C_Session::C_Session(asio::io_service& IOService)
: m_Socket(IOService)
{
	m_eState.store(E_State_WaitingOrConnecting);
	m_bReading.store(false);
	m_bSending.store(false);
}


C_Session::~C_Session()
{
 
}

C_Session::E_State C_Session::State() 
{
	return (E_State)m_eState.load();
}

void C_Session::Close() 
{
	m_eState.store(E_State_Close, std::memory_order_relaxed);
}

bool C_Session::Send(uint8_t const* pData, uint32_t uLen) 
{
	auto uRealLen = m_SendRingBuffer.Write(pData, uLen);
	PostSend();
	return true;
}


bool C_Session::PostSend()
{
	bool bOldValue = false;
	if (!m_bSending.compare_exchange_strong(bOldValue, true, std::memory_order_relaxed)) // 设置为发送中
	{
		return false;
	}

	uint8_t* pReadBuff;
	uint32_t uLen = 0;
	m_SendRingBuffer.GetNextReadData(pReadBuff, uLen);
	if (uLen == 0) // no buff
	{
		m_bSending.store(false, std::memory_order_relaxed);
		return false;
	}

	auto pSelfI = shared_from_this();
	auto pSelf = std::dynamic_pointer_cast<C_Session>(pSelfI);
	asio::async_write(
		m_Socket
		, asio::buffer(pReadBuff, uLen)
		, boost::bind(&C_Session::OnSend, pSelf, asio::placeholders::error, asio::placeholders::bytes_transferred)
	);
	return true;
}


void C_Session::OnSend(asio::error_code const& error, size_t const bytes)
{
	if (error)
	{
		Close();
		return;
	}

	m_SendRingBuffer.IncReadDataLength(bytes);
	m_bSending.store(false, std::memory_order_relaxed);
	PostSend();
}

bool C_Session::PostRead()
{
	bool bOldValue = false;
	if (!m_bReading.compare_exchange_strong(bOldValue, true, std::memory_order_relaxed)) // 设置为读取中
	{
		return false;
	}

	uint8_t* pWriteBuff;
	uint32_t uLen = 0;
	m_ReadRingBuffer.GetNextWriteData(pWriteBuff, uLen);
	if (uLen == 0) // no buff
	{
		m_bReading.store(false, std::memory_order_relaxed);
		return false;
	}

	auto pSelfI = shared_from_this();
	auto pSelf = std::dynamic_pointer_cast<C_Session>(pSelfI);
	asio::async_read(
		m_Socket
		, asio::buffer(pWriteBuff, uLen)
		, asio::transfer_at_least(1)
		, boost::bind(&C_Session::OnRead, pSelf, asio::placeholders::error, asio::placeholders::bytes_transferred)
	);
	return true;
}


void C_Session::OnRead(asio::error_code const& error, size_t const bytes)
{
	if (error)
	{
		Close();
		return;
	}

	m_ReadRingBuffer.IncWriteDataLength(bytes);
	m_bReading.store(false, std::memory_order_relaxed);
	PostRead();
}


bool C_Session::Recv(T_RecvBuffers& buffers)
{
	auto uSize = m_ReadRingBuffer.Size();
	if (uSize == 0)
	{
		return true;
	}

	auto pData = new uint8_t[uSize];
	auto uRealLen = m_ReadRingBuffer.Read(pData, uSize);
	delete [] pData;
	assert(uRealLen == uSize);
	m_ReadRingBuffer.IncReadDataLength(uRealLen);

	PostRead();
	return true;
}

void C_Session::OnAccept() {
	m_eState.store(E_State_Established);
	PostRead();
}

void C_Session::OnConnect() {
	m_eState.store(E_State_Established);
	PostRead();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
