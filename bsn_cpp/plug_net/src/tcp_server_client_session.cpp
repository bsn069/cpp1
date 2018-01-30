#include <bsn_cpp/plug_net/src/tcp_server_client_session.h>
#include <bsn_cpp/plug_net/src/tcp_server.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_TCPServerClientSession::C_TCPServerClientSession(C_TCPServer::T_SPC_TCPServer spC_TCPServer) 
	: m_spC_TCPServer(spC_TCPServer) 
	, m_Socket(spC_TCPServer->m_IOService) {
	D_OutInfo();
}

C_TCPServerClientSession::~C_TCPServerClientSession() {
	D_OutInfo();
 
}

bool C_TCPServerClientSession::Start() {
	D_OutInfo();
    boost::asio::spawn(
		m_spC_TCPServer->m_IOService
		, boost::bind(
			&C_TCPServerClientSession::RunCoro
			, GetSPC_TCPServerClientSession()
			, _1
		)
	);
	return true;	
}

bool C_TCPServerClientSession::Stop() {
	D_OutInfo();
	m_Socket.close();
	return true;	
}
	
C_TCPServerClientSession::T_SPC_TCPServerClientSession C_TCPServerClientSession::GetSPC_TCPServerClientSession() {
	D_OutInfo();
	auto spI_TCPServerClientSession = GetSPI_TCPServerClientSession();
	auto spC_TCPServerClientSession = std::dynamic_pointer_cast<C_TCPServerClientSession>(spI_TCPServerClientSession);
	return spC_TCPServerClientSession;
}
 
void C_TCPServerClientSession::RunCoro(boost::asio::yield_context yield) {
	D_OutInfo();
	boost::system::error_code ec; 

	auto yield_ec = yield[ec];
	while (true) {
		auto bytes_transferred = m_Socket.async_read_some(
			boost::asio::buffer(m_Buffer)
			, yield_ec
		);
		if (ec) {  
			D_OutInfo1(boost::system::system_error(ec).what());  
			if (ec != boost::asio::error::operation_aborted) {
				m_spC_TCPServer->Stop(GetSPC_TCPServerClientSession()); 
			}
			break;
		} 
		std::string strInfo(m_Buffer.data(), bytes_transferred);
		D_OutInfo1(strInfo);

		bytes_transferred = boost::asio::async_write(
			m_Socket
			, boost::asio::buffer(m_Buffer, bytes_transferred)
			, boost::asio::transfer_all()
			, yield[ec]
		);
		if (ec) {  
			D_OutInfo1(boost::system::system_error(ec).what());   
			return;
		} 
	}
}

//////////////////////////////////////////////////////////////////////
C_TCPServerClientSession* CreateC_TCPServerClientSession(C_TCPServer::T_SPC_TCPServer spC_TCPServer) {
	D_OutInfo();
	C_TCPServerClientSession* pC_TCPServerClientSession = New<C_TCPServerClientSession>(spC_TCPServer);
	return pC_TCPServerClientSession;
}

void ReleaseC_TCPServerClientSession(I_TCPServerClientSession* pI_TCPServerClientSession) {
	D_OutInfo();
	C_TCPServerClientSession* pC_TCPServerClientSession = static_cast<C_TCPServerClientSession*>(pI_TCPServerClientSession);
	Delete(pC_TCPServerClientSession);
}

C_TCPServerClientSession::T_SPC_TCPServerClientSession C_TCPServerClientSession::NewC_TCPServerClientSession(C_TCPServer::T_SPC_TCPServer spC_TCPServer) {
	D_OutInfo();
	auto pC_TCPServerClientSession = CreateC_TCPServerClientSession(spC_TCPServer);
	auto spC_TCPServerClientSession = C_TCPServerClientSession::T_SPC_TCPServerClientSession(pC_TCPServerClientSession, ReleaseC_TCPServerClientSession);
	return spC_TCPServerClientSession;
}

C_TCPServerClientSession::T_SPI_TCPServerClientSession C_TCPServerClientSession::NewI_TCPServerClientSession(C_TCPServer::T_SPC_TCPServer spC_TCPServer) {
	D_OutInfo();
	auto spC_TCPServerClientSession = C_TCPServerClientSession::NewC_TCPServerClientSession(spC_TCPServer);
	auto spI_TCPServerClientSession = spC_TCPServerClientSession->GetSPI_TCPServerClientSession();
	return spI_TCPServerClientSession;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif