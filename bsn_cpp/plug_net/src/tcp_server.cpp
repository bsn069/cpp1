#include <bsn_cpp/plug_net/src/tcp_server.h>
#include <bsn_cpp/plug_net/src/tcp_server_client_session.h>
#include <bsn_cpp/plug_net/src/dns.h>
#include <bsn_cpp/plug_net/src/url.h>
 
#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>

using namespace boost::asio::ip::tcp;

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_TCPServer::C_TCPServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet) 
	: m_spC_PlugNet(spC_PlugNet)
	, m_IOService(spC_PlugNet->GetIOService()) 
	, m_Acceptor(m_IOService)
	, m_bListen(false) {
	D_OutInfo();
}

C_TCPServer::~C_TCPServer() {
	D_OutInfo();
	Stop();
}

C_TCPServer::T_SPC_TCPServer C_TCPServer::GetSPC_TCPServer() {
	D_OutInfo();
	auto spI_TCPSC_TCPServer = GetSPI_TCPSC_TCPServer();
	auto spC_TCPServer = std::dynamic_pointer_cast<C_TCPServer>(spI_TCPSC_TCPServer);
	return spC_TCPServer;
}

I_Address::T_SPI_Address C_TCPServer::GetAddress() {
	return m_spI_Address;
}

bool C_TCPServer::SetAddress(I_Address::T_SPI_Address spI_Address) {
	auto const& strHost = spI_Address->GetAddr();
	if (strHost.empty()) {
		D_OutInfo1("host is empty");
		return false;
	}

	auto u16Port = spI_Address->GetPort();
	if (u16Port == 0) {
		D_OutInfo1("not set port");
		return false;
	}

	m_spI_Address = spI_Address;
	return true;
}

bool C_TCPServer::Start() {
	StartListen();
	return true;
}

bool C_TCPServer::Stop() {
	StopListen();
	StopAllClient();
	return true;
}

bool C_TCPServer::StartListen() {
	D_OutInfo();
    boost::asio::spawn(
		m_IOService
		, boost::bind(
			&C_TCPServer::ListenCoro
			, GetSPC_TCPServer()
			, _1
		)
	);
	return true;
}

bool C_TCPServer::StopListen() {
	m_Acceptor.close();
	m_bListen = false;
	return true;
}

bool C_TCPServer::StopAllClient() {
	for (auto& session : m_ClientSessions) {
		session->StopSession();
	}
	m_ClientSessions.clear();
	return true;
}

bool C_TCPServer::StartSession(T_SPC_TCPServerClientSession session) {
	m_ClientSessions.insert(session);
	session->Start();
	return true;
}

bool C_TCPServer::StopSession(T_SPC_TCPServerClientSession session) {
	m_ClientSessions.erase(session);
	session->Stop();
	return true;
}

void C_TCPServer::ListenCoro(boost::asio::yield_context yield) {
	D_OutInfo();

	if (m_bListen) {
		D_OutInfo1("listening");
		return;
	}

	auto Address = GetAddress();
	if (!Address) {
		D_OutInfo1("not set address");
		return;
	}
	
	if (m_Acceptor.is_open()) {
		D_OutInfo1("had open");
		return;
	}

	m_bListen = true;
	boost::system::error_code ec; 

	{
		resolver 	Resover(m_IOService);
		resolver::query Query(
			spI_Address->GetAddr()
			, boost::lexical_cast<std::string>(spI_Address->GetPort())
		);
		auto EndPointItor = Resover.async_resolve(Query, yield[ec]);
		if (ec) { 
			m_bListen = false; 
			D_OutInfo1(boost::system::system_error(ec).what());   
			return;
		} 

		auto EndPoint = EndPointItor->endpoint();
		m_Acceptor.open(EndPoint.protocol());
		m_Acceptor.set_option(acceptor::reuse_address(true));
		m_Acceptor.bind(EndPoint);
		m_Acceptor.listen();
	}

	auto yield_ec = yield[ec];
	auto spC_TCPServer = GetSPC_TCPServer();
	while (m_Acceptor.is_open()) {
		auto spC_TCPServerClientSession = C_TCPServerClientSession::NewC_TCPServerClientSession(spC_TCPServer);
		m_Acceptor.async_accept(spC_TCPServerClientSession->m_Socket, yield_ec);
		if (ec) {  
			D_OutInfo1(boost::system::system_error(ec).what());   
			break;
		}
		D_OutInfo1("on client connect");
		StartSession(spC_TCPServerClientSession);
	}
	m_bListen = false;
	D_OutInfo();
}

//////////////////////////////////////////////////////////////////////
C_TCPServer* CreateC_TCPServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	C_TCPServer* pC_TCPServer = New<C_TCPServer>(spC_PlugNet);
	return pC_TCPServer;
}

void ReleaseC_TCPServer(I_TCPSC_TCPServer* pI_TCPSC_TCPServer) {
	D_OutInfo();
	C_TCPServer* pC_TCPServer = static_cast<C_TCPServer*>(pI_TCPSC_TCPServer);
	Delete(pC_TCPServer);
}

C_TCPServer::T_SPC_TCPServer C_TCPServer::NewC_TCPServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto pC_TCPServer = CreateC_TCPServer(spC_PlugNet);
	auto spC_TCPServer = C_TCPServer::T_SPC_TCPServer(pC_TCPServer, ReleaseC_TCPServer);
	return spC_TCPServer;
}

C_TCPServer::T_SPI_TCPSC_TCPServer C_TCPServer::NewI_TCPSC_TCPServer(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto spC_TCPServer = C_TCPServer::NewC_TCPServer(spC_PlugNet);
	auto spI_TCPSC_TCPServer = spC_TCPServer->GetSPI_TCPSC_TCPServer();
	return spI_TCPSC_TCPServer;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif