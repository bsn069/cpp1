#include <bsn_cpp/plug_net/src/tcp_connect.h>
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
C_TCPConnect::C_TCPConnect(C_PlugNet::T_SPC_PlugNet spC_PlugNet) 
	: m_spC_PlugNet(spC_PlugNet)
	, m_IOService(spC_PlugNet->GetIOService()) {
	D_OutInfo();
}

C_TCPConnect::~C_TCPConnect() {
	D_OutInfo();
	m_spC_PlugNet = nullptr;
}

C_TCPConnect::T_SPC_TCPConnect C_TCPConnect::GetSPC_TCPConnect() {
	D_OutInfo();
	auto spI_TCPConnect = GetSPI_TCPConnect();
	auto spC_TCPConnect = std::dynamic_pointer_cast<C_TCPConnect>(spI_TCPConnect);
	return spC_TCPConnect;
}

bool C_TCPConnect::CanConnect(I_TCPSession::T_SPI_TCPSession spI_TCPSession) {
	D_OutInfo();

	if (!spI_TCPSession) {
		D_OutInfo1("!spI_TCPSession");
		return false;
	}

	auto eType = spI_TCPSession->GetType();
	if (eType != I_TCPSession::E_Type_Connect) {
		D_OutInfo2("eType must equal I_TCPSession::E_Type_Connect", eType);
		return false;
	}

	auto eState = spI_TCPSession->GetState();
	if (eState != I_TCPSession::E_State_Null) {
		D_OutInfo2("eState=%u must equal I_TCPSession::E_State_Null", eState);
		return false;
	}

	return true;
}

bool C_TCPConnect::Connect(
	I_TCPSession::T_SPI_TCPSession spI_TCPSession
	, I_Address::T_SPI_Address spI_Address
	, T_FuncOnConnect func
) {
	D_OutInfo();

	if (!CanConnect(spI_TCPSession)) {
		D_OutInfo1("can't connect");
		return false;
	}

    boost::asio::spawn(
		m_IOService
		, boost::bind(
			&C_TCPConnect::ConnectCoro
			, GetSPC_TCPConnect()
			, _1
			, spI_TCPSession
			, spI_Address
			, func
		)
	);
	return true;
}

void C_TCPConnect::ConnectCoro(
	boost::asio::yield_context yield
	, I_TCPSession::T_SPI_TCPSession spI_TCPSession
	, I_Address::T_SPI_Address spI_Address
	, T_FuncOnConnect func
) {
	D_OutInfo();

	if (!CanConnect(spI_TCPSession)) {
		D_OutInfo1("can't connect");
		return;
	}
	
	boost::system::error_code ec; 
	spI_TCPSession->SetState(I_TCPSession::E_State_Connecting);

	tcp::resolver 	Resover(m_IOService);
	tcp::resolver::query Query(
		spI_Address->GetAddr()
		, boost::lexical_cast<std::string>(spI_Address->GetPort())
	);
	auto yield_ec = yield[ec];
	auto EndPointItor = Resover.async_resolve(Query, yield_ec);
	if (!ec) {
		boost::asio::async_connect(
			spI_TCPSession->GetSocket()
			, EndPointItor
			, yield_ec
		);
		if (!ec) {
			spI_TCPSession->SetState(I_TCPSession::E_State_Connected);
			D_OutInfo1("connect success");
		}
	}

	if (ec) { 
		D_OutInfo1("connect fail");
		D_OutInfo1(boost::system::system_error(ec).what());   
	} 

	if (func) {
		func(spI_TCPSession);
	}
}

//////////////////////////////////////////////////////////////////////
C_TCPConnect* CreateC_TCPConnect(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	C_TCPConnect* pC_TCPConnect = New<C_TCPConnect>(spC_PlugNet);
	return pC_TCPConnect;
}

void ReleaseC_TCPConnect(I_TCPConnect* pI_TCPConnect) {
	D_OutInfo();
	C_TCPConnect* pC_TCPConnect = static_cast<C_TCPConnect*>(pI_TCPConnect);
	Delete(pC_TCPConnect);
}

C_TCPConnect::T_SPC_TCPConnect C_TCPConnect::NewC_TCPConnect(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto pC_TCPConnect = CreateC_TCPConnect(spC_PlugNet);
	auto spC_TCPConnect = C_TCPConnect::T_SPC_TCPConnect(pC_TCPConnect, ReleaseC_TCPConnect);
	return spC_TCPConnect;
}

C_TCPConnect::T_SPI_TCPConnect C_TCPConnect::NewI_TCPConnect(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto spC_TCPConnect = C_TCPConnect::NewC_TCPConnect(spC_PlugNet);
	auto spI_TCPConnect = spC_TCPConnect->GetSPI_TCPConnect();
	return spI_TCPConnect;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif