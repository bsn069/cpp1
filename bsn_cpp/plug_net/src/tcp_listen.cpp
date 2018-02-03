#include <bsn_cpp/plug_net/src/tcp_listen.h>
#include <bsn_cpp/plug_net/src/dns.h>
#include <bsn_cpp/plug_net/src/url.h>
 
#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>

using namespace boost::asio::ip;

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_TCPListen::C_TCPListen(C_PlugNet::T_SPC_PlugNet spC_PlugNet) 
	: m_spC_PlugNet(spC_PlugNet)
	, m_IOService(spC_PlugNet->GetIOService()) 
	, m_Acceptor(m_IOService)
	, m_bListen(false) {
	D_OutInfo();
}

C_TCPListen::~C_TCPListen() {
	D_OutInfo();
}

C_TCPListen::T_SPC_TCPListen C_TCPListen::GetSPC_TCPListen() {
	D_OutInfo();
	auto spI_TCPListen = GetSPI_TCPListen();
	auto spC_TCPListen = std::dynamic_pointer_cast<C_TCPListen>(spI_TCPListen);
	return spC_TCPListen;
}

I_Address::T_SPI_Address C_TCPListen::GetAddress() {
	return m_spI_Address;
}

bool C_TCPListen::SetAddress(I_Address::T_SPI_Address spI_Address) {
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

void C_TCPListen::SetFuncNew(T_FuncNew func) {

}

void C_TCPListen::SetFuncOnAccept(T_FuncOnAccept func) {

}



bool C_TCPListen::StartListen() {
	D_OutInfo();
    boost::asio::spawn(
		m_IOService
		, boost::bind(
			&C_TCPListen::ListenCoro
			, GetSPC_TCPListen()
			, _1
		)
	);
	return true;
}

bool C_TCPListen::StopListen() {
	m_Acceptor.close();
	m_bListen = false;
	return true;
}

void C_TCPListen::ListenCoro(boost::asio::yield_context yield) {
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
		tcp::resolver 	Resover(m_IOService);
		tcp::resolver::query Query(
			Address->GetAddr()
			, boost::lexical_cast<std::string>(Address->GetPort())
		);
		auto EndPointItor = Resover.async_resolve(Query, yield[ec]);
		if (ec) { 
			m_bListen = false; 
			D_OutInfo1(boost::system::system_error(ec).what());   
			return;
		} 

		auto EndPoint = EndPointItor->endpoint();
		m_Acceptor.open(EndPoint.protocol());
		m_Acceptor.set_option(tcp::acceptor::reuse_address(true));
		m_Acceptor.bind(EndPoint);
		m_Acceptor.listen();
	}

	auto yield_ec = yield[ec];
	auto spC_TCPListen = GetSPC_TCPListen();
	while (m_Acceptor.is_open()) {
		I_TCPSession::T_SPI_TCPSession spI_TCPSession = m_FuncNew();
		m_Acceptor.async_accept(spI_TCPSession->GetSocket(), yield_ec);
		if (ec) {  
			D_OutInfo1(boost::system::system_error(ec).what());   
			break;
		}
		D_OutInfo1("on client connect");
		m_FuncOnAccept(spI_TCPSession);
	}
	m_bListen = false;
	D_OutInfo();
}

//////////////////////////////////////////////////////////////////////
C_TCPListen* CreateC_TCPListen(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	C_TCPListen* pC_TCPListen = New<C_TCPListen>(spC_PlugNet);
	return pC_TCPListen;
}

void ReleaseC_TCPListen(I_TCPListen* pI_TCPListen) {
	D_OutInfo();
	C_TCPListen* pC_TCPListen = static_cast<C_TCPListen*>(pI_TCPListen);
	Delete(pC_TCPListen);
}

C_TCPListen::T_SPC_TCPListen C_TCPListen::NewC_TCPListen(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto pC_TCPListen = CreateC_TCPListen(spC_PlugNet);
	auto spC_TCPListen = C_TCPListen::T_SPC_TCPListen(pC_TCPListen, ReleaseC_TCPListen);
	return spC_TCPListen;
}

C_TCPListen::T_SPI_TCPListen C_TCPListen::NewI_TCPListen(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto spC_TCPListen = C_TCPListen::NewC_TCPListen(spC_PlugNet);
	auto spI_TCPListen = spC_TCPListen->GetSPI_TCPListen();
	return spI_TCPListen;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif