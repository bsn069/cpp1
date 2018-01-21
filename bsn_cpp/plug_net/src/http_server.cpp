#include <bsn_cpp/plug_net/src/http_server.h>
#include <bsn_cpp/plug_net/src/http_server_client_session.h>
#include <bsn_cpp/plug_net/src/dns.h>
#include <bsn_cpp/plug_net/src/url.h>
 
#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_HttpServer::C_HttpServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet) 
	: m_spC_PlugNet(spC_PlugNet)
	, m_IOService(spC_PlugNet->GetIOService()) 
	, m_Acceptor(m_IOService) {
	D_OutInfo();
}

C_HttpServer::~C_HttpServer() {
	D_OutInfo();
	Stop();
}

C_HttpServer::T_SPC_HttpServer C_HttpServer::GetSPC_HttpServer() {
	D_OutInfo();
	auto spI_HttpServer = GetSPI_HttpServer();
	auto spC_HttpServer = std::dynamic_pointer_cast<C_HttpServer>(spI_HttpServer);
	return spC_HttpServer;
}

I_Address::T_SPI_Address C_HttpServer::GetAddress() {
	return m_spI_Address;
}

void C_HttpServer::SetAddress(I_Address::T_SPI_Address spI_Address) {
	m_spI_Address = spI_Address;
}

bool C_HttpServer::Start() {
	auto Address = GetAddress();
	if (!Address) {
		return false;
	}

	if (m_Acceptor.is_open()) {
		return true;
	}

    boost::asio::spawn(
		m_IOService
		, boost::bind(
			&C_HttpServer::RunCoroutineImp
			, GetSPC_HttpServer()
			, _1
		)
	);
	return true;
}

bool C_HttpServer::Stop() {
	m_Acceptor.close();
	StopAllClient();
	return true;
}

bool C_HttpServer::StopAllClient() {
	for (auto& session : m_ClientSessions) {
		session->Stop();
	}
	m_ClientSessions.clear();
	return true;
}

bool C_HttpServer::Start(T_SPC_HttpServerClientSession session) {
	m_ClientSessions.insert(session);
	session->Start();
	return true;
}


bool C_HttpServer::Stop(T_SPC_HttpServerClientSession session) {
	m_ClientSessions.erase(session);
	session->Stop();
	return true;
}

void C_HttpServer::RunCoroutineImp(boost::asio::yield_context yield) {
	boost::system::error_code ec; 

	auto Address = GetAddress();
	auto const& strHost = Address->GetAddr();
	auto u16Port = Address->GetPort();
// boost::asio::ip::tcp::resolver resolver(io_service_);
//   boost::asio::ip::tcp::resolver::query query(address, port);
//   boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
//   acceptor_.open(endpoint.protocol());
//   acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
//   acceptor_.bind(endpoint);
//   acceptor_.listen();

	boost::asio::ip::tcp::resolver 	Resover(m_IOService);
	boost::asio::ip::tcp::resolver::query Query(strHost, boost::lexical_cast<std::string>(u16Port));
	auto EndPointItor = Resover.async_resolve(Query, yield[ec]);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 

	auto EndPoint = EndPointItor->endpoint();
	m_Acceptor.open(EndPoint.protocol());
	m_Acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_Acceptor.bind(EndPoint);
	m_Acceptor.listen();

	while (m_Acceptor.is_open()) {
		auto spC_HttpServerClientSession = C_HttpServerClientSession::NewC_HttpServerClientSession(GetSPC_HttpServer());
		m_Acceptor.async_accept(spC_HttpServerClientSession->m_Socket, yield[ec]);
		if (ec) {  
			D_OutInfo1(boost::system::system_error(ec).what());   
			return;
		}
		D_OutInfo1("on client connect");
		Start(spC_HttpServerClientSession);
	}
}

//////////////////////////////////////////////////////////////////////
C_HttpServer* CreateC_HttpServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	C_HttpServer* pC_HttpServer = New<C_HttpServer>(spC_PlugNet);
	return pC_HttpServer;
}

void ReleaseC_HttpServer(I_HttpServer* pI_HttpServer) {
	D_OutInfo();
	C_HttpServer* pC_HttpServer = static_cast<C_HttpServer*>(pI_HttpServer);
	Delete(pC_HttpServer);
}

C_HttpServer::T_SPC_HttpServer C_HttpServer::NewC_HttpServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto pC_HttpServer = CreateC_HttpServer(spC_PlugNet);
	auto spC_HttpServer = C_HttpServer::T_SPC_HttpServer(pC_HttpServer, ReleaseC_HttpServer);
	return spC_HttpServer;
}

C_HttpServer::T_SPI_HttpServer C_HttpServer::NewI_HttpServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto spC_HttpServer = C_HttpServer::NewC_HttpServer(spC_PlugNet);
	auto spI_HttpServer = spC_HttpServer->GetSPI_HttpServer();
	return spI_HttpServer;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif