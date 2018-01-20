#include <bsn_cpp/plug_net/src/http_server.h>
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
	: m_spC_PlugNet(spC_PlugNet) {
	D_OutInfo();
}

C_HttpServer::~C_HttpServer() {
	D_OutInfo();
 
}

C_HttpServer::T_SPC_HttpServer C_HttpServer::GetSPC_HttpServer() {
	D_OutInfo();
	auto spI_HttpServer = GetSPI_HttpServer();
	auto spC_HttpServer = std::dynamic_pointer_cast<C_HttpServer>(spI_HttpServer);
	return spC_HttpServer;
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