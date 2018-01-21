#include <bsn_cpp/plug_net/src/http_server_client_session.h>
#include <bsn_cpp/plug_net/src/http_server.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_HttpServerClientSession::C_HttpServerClientSession(C_HttpServer::T_SPC_HttpServer spC_HttpServer, boost::asio::ip::tcp::socket Socket) 
	: m_spC_HttpServer(spC_HttpServer) 
	, m_Socket(std::move(Socket)) {
	D_OutInfo();
}

C_HttpServerClientSession::~C_HttpServerClientSession() {
	D_OutInfo();
 
}

bool C_HttpServerClientSession::Start() {
    boost::asio::spawn(
		m_spC_HttpServer->m_IOService
		, boost::bind(
			&C_HttpServerClientSession::RunCoroutineImp
			, GetSPC_HttpServerClientSession()
			, _1
		)
	);
	return true;	
}

bool C_HttpServerClientSession::Stop() {
	m_Socket.close();
	return true;	
}

	
C_HttpServerClientSession::T_SPC_HttpServerClientSession C_HttpServerClientSession::GetSPC_HttpServerClientSession() {
	D_OutInfo();
	auto spI_HttpServerClientSession = GetSPI_HttpServerClientSession();
	auto spC_HttpServerClientSession = std::dynamic_pointer_cast<C_HttpServerClientSession>(spI_HttpServerClientSession);
	return spC_HttpServerClientSession;
}
 
void C_HttpServerClientSession::RunCoroutineImp(boost::asio::yield_context yield) {
	boost::system::error_code ec; 

	while (true) {
		auto bytes_transferred = m_Socket.async_read_some(boost::asio::buffer(m_Buffer), yield[ec]);
		if (ec) {  
			D_OutInfo1(boost::system::system_error(ec).what());  
			if (ec != boost::asio::error::operation_aborted) {
				m_spC_HttpServer->Stop(GetSPC_HttpServerClientSession()); 
			}
			return;
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
C_HttpServerClientSession* CreateC_HttpServerClientSession(C_HttpServer::T_SPC_HttpServer spC_HttpServer, boost::asio::ip::tcp::socket Socket) {
	D_OutInfo();
	C_HttpServerClientSession* pC_HttpServerClientSession = New<C_HttpServerClientSession>(spC_HttpServer, std::move(Socket));
	return pC_HttpServerClientSession;
}

void ReleaseC_HttpServerClientSession(I_HttpServerClientSession* pI_HttpServerClientSession) {
	D_OutInfo();
	C_HttpServerClientSession* pC_HttpServerClientSession = static_cast<C_HttpServerClientSession*>(pI_HttpServerClientSession);
	Delete(pC_HttpServerClientSession);
}

C_HttpServerClientSession::T_SPC_HttpServerClientSession C_HttpServerClientSession::NewC_HttpServerClientSession(C_HttpServer::T_SPC_HttpServer spC_HttpServer, boost::asio::ip::tcp::socket Socket) {
	D_OutInfo();
	auto pC_HttpServerClientSession = CreateC_HttpServerClientSession(spC_HttpServer, std::move(Socket));
	auto spC_HttpServerClientSession = C_HttpServerClientSession::T_SPC_HttpServerClientSession(pC_HttpServerClientSession, ReleaseC_HttpServerClientSession);
	return spC_HttpServerClientSession;
}

C_HttpServerClientSession::T_SPI_HttpServerClientSession C_HttpServerClientSession::NewI_HttpServerClientSession(C_HttpServer::T_SPC_HttpServer spC_HttpServer, boost::asio::ip::tcp::socket Socket) {
	D_OutInfo();
	auto spC_HttpServerClientSession = C_HttpServerClientSession::NewC_HttpServerClientSession(spC_HttpServer, std::move(Socket));
	auto spI_HttpServerClientSession = spC_HttpServerClientSession->GetSPI_HttpServerClientSession();
	return spI_HttpServerClientSession;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif