#include "session.h"
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>
#include <boost/bind.hpp>
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
C_Session::C_Session(boost::asio::io_service& io, D_N1(common)::I_Common::T_SPI_Common spI_Common)
	: m_Socket(io)
	, m_eState(E_State_Connecting)
	, m_bCanCommitSendData(true)
{
	auto pAlloc = spI_Common->GetGlobalAlloc(D_N1(common)::I_Alloc::Raw);
	m_spI_BufferWaitSend	= spI_Common->NewBuffer(pAlloc, 4096);
	m_spI_BufferSending		= spI_Common->NewBuffer(pAlloc, 4096);
}

C_Session::~C_Session() {
	m_spI_BufferWaitSend 	= nullptr;
	m_spI_BufferSending 	= nullptr;
}

void 
C_Session::Close() 
{
	m_eState = E_State_Close;
}

bool 
C_Session::IsWork() 
{
	return m_eState == E_State_Established;
}

bool 
C_Session::CommitSendData() {
	if (!IsWork()) {
		return false;
	}
	if (!m_bCanCommitSendData) {
		return false;
	}

	auto leftByte = m_spI_BufferSending->GetCanReadLength();
	if (leftByte <= 0) {
		auto waitSendByte = m_spI_BufferWaitSend->GetCanReadLength();
		if (waitSendByte <= 0) {
			return true;
		}
		m_spI_BufferSending.swap(m_spI_BufferWaitSend);
	}

	auto waitSendByte = m_spI_BufferSending->GetCanReadLength();
	D_Assert(waitSendByte > 0);

	auto pData = m_spI_BufferSending->GetReadPtr();
	auto pSelfI = shared_from_this();
	auto pSelf = std::dynamic_pointer_cast<C_Session>(pSelfI);
	boost::asio::async_write(
		GetSocket()
		, boost::asio::buffer(pData, waitSendByte)
		, boost::bind(
			&C_Session::OnSend
			, pSelf
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred
		)
	);
	m_bCanCommitSendData = false;
	return true;
}

bool 
C_Session::Send(uint8_t const* pData, uint32_t u32Len) {
	D_Assert(pData);
	D_Assert(u32Len > 0);

	m_spI_BufferWaitSend->Write(pData, u32Len);
	CommitSendData();
	return true;
}

void 
C_Session::OnSend(boost::system::error_code const& error, size_t const bytes) {
	D_Assert(!m_bCanCommitSendData);
	m_bCanCommitSendData = true;

	if (bytes > 0) {
		m_spI_BufferSending->Read(bytes);
	}

	if (error) {
		Close();
		return;
	}

	CommitSendData();
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
