#include <bsn_cpp/plug_net/src/send_mail.h>
#include <bsn_cpp/plug_net/src/dns.h>
#include <bsn_cpp/plug_net/src/url.h>
 
#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/format.hpp>

#include <iostream>
#include <istream>

// using boost::asio::ip;
using namespace boost::asio::ip;

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_SendMail::C_SendMail(C_PlugNet::T_SPC_PlugNet spC_PlugNet) 
	: m_spC_PlugNet(spC_PlugNet)
	, m_Socket(spC_PlugNet->GetIOService()) {
	D_OutInfo();

	m_bHadConnect 	= false;
	m_bHadLogin 	= false;
	m_bSending 		= false;
	m_u16Port 		= 25;
}

C_SendMail::~C_SendMail() {
	D_OutInfo();
 
}

C_SendMail::T_SPC_SendMail C_SendMail::GetSPC_SendMail() {
	D_OutInfo();
	auto spI_SendMail = GetSPI_SendMail();
	auto spC_SendMail = std::dynamic_pointer_cast<C_SendMail>(spI_SendMail);
	return spC_SendMail;
}
 
void C_SendMail::SendTest() {
	D_OutInfo();

	m_strSmtpHost = "smtp.163.com";

	m_strUserBase64 = "YnNuXzE2M0AxNjMuY29t";
	m_strPwdBase64 = "WG8zSjJwMDQwTXVz";

	m_strMailFrom = "bsn_163@163.com";
	m_strMailTo = "15914057651@139.com";
	m_strMailSubject = "subject";
	m_strMailContent = "content";

    boost::asio::spawn(m_spC_PlugNet->GetIOService(),
        boost::bind(&C_SendMail::SendMailCoro,
          GetSPC_SendMail(), _1));
}

void C_SendMail::Cmd(
	boost::asio::yield_context yield
	, std::string const& strSend
	, uint32_t& u32RetCode
) {
	boost::system::error_code ec;
	boost::asio::streambuf response;  
	std::istream is(&response);  
	is.unsetf(std::ios_base::skipws);  
	std::string strData;  
	u32RetCode = 0;

	D_OutInfo2("strSend=", strSend);

	if (!strSend.empty()) {
		boost::asio::async_write(
			m_Socket
			, boost::asio::buffer(strSend.data(), strSend.size())
			, yield[ec]
		); 
		if (ec) {  
			D_OutInfo1(boost::system::system_error(ec).what());   
			return;
		} 
	}
	
	D_OutInfo1("wait rsp");
	boost::asio::async_read_until(
		m_Socket
		, response
		, "\n"
		, yield[ec]
	);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 
	is >> u32RetCode;
	getline(is, strData);
	D_OutInfo3("ret code=", u32RetCode, strData);
}

void C_SendMail::SendMailCoro(boost::asio::yield_context yield) {
	D_OutInfo();

	ConnectCoro(yield);
	if (!m_bHadConnect) {
		return;
	}

	LoginCoro(yield);
	if (!m_bHadLogin) {
		return;
	}

	SendCoro(yield);
}

void C_SendMail::ConnectCoro(boost::asio::yield_context yield) {
	D_OutInfo();

	if (m_bHadConnect) {
		return;
	}
	boost::system::error_code ec; 

    tcp::resolver::query    Query(m_strSmtpHost, boost::lexical_cast<std::string>(m_u16Port));
	tcp::resolver           Resolver(m_spC_PlugNet->GetIOService());
	auto endpoint_iterator = Resolver.async_resolve(Query, yield[ec]);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 
	D_OutInfo1("resolve success");

	boost::asio::async_connect(m_Socket, endpoint_iterator, yield[ec]);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 
	D_OutInfo1("connect success");

	m_bHadConnect = true;
}

void C_SendMail::LoginCoro(boost::asio::yield_context yield) {
	D_OutInfo();
	boost::system::error_code ec; 
	uint32_t u32RetCode;
	std::string strSend;

	if (!m_bHadConnect) {
		return;
	}

	if (m_bHadLogin) {
		return;
	}

	Cmd(yield, "", u32RetCode);
	if (u32RetCode != 220) {
		return;
	}

	Cmd(yield, "helo s\r\n", u32RetCode);
 	if (u32RetCode != 250) {
		return;
	}

	Cmd(yield, "auth login\r\n", u32RetCode);
 	if (u32RetCode != 334) {
		return;
	}
	
	strSend = boost::str(boost::format("%1%\r\n") % m_strUserBase64); 
	Cmd(yield, strSend, u32RetCode);
 	if (u32RetCode != 334) {
		return;
	}

	strSend = boost::str(boost::format("%1%\r\n") % m_strPwdBase64); 
	Cmd(yield, strSend, u32RetCode);
 	if (u32RetCode != 235) {
		return;
	}

	m_bHadLogin = true;
}

void C_SendMail::SendCoro(boost::asio::yield_context yield) {
	D_OutInfo();
	boost::system::error_code ec; 
	uint32_t u32RetCode;
	std::string strSend;

	if (m_bSending) {
		return;
	}

	if (!m_bHadLogin) {
		return;
	}

	m_bSending = true;

	strSend = boost::str(boost::format("mail from:<%1%>\r\n") % m_strMailFrom); 
	Cmd(yield, strSend, u32RetCode);
	if (u32RetCode != 250) {
		m_bSending = false;
		return;
	}

	strSend = boost::str(boost::format("rcpt to:<%1%>\r\n") % m_strMailTo); 
	Cmd(yield, strSend, u32RetCode);
 	if (u32RetCode != 250) {
		m_bSending = false;
		return;
	}

	Cmd(yield, "data\r\n", u32RetCode);
 	if (u32RetCode != 354) {
		m_bSending = false;
		return;
	}
	
	strSend = boost::str(boost::format("From:%1%\r\nTo:%2%\r\nSubject:%3%\r\n\r\n%4%\r\n.\r\n") 
		% m_strMailFrom
		% m_strMailTo
		% m_strMailSubject
		% m_strMailContent
	); 
	Cmd(yield, strSend, u32RetCode);
 	if (u32RetCode != 250) {
		m_bSending = false;
		return;
	}
	m_bSending = false;
}
//////////////////////////////////////////////////////////////////////
C_SendMail* CreateC_SendMail(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	C_SendMail* pC_SendMail = New<C_SendMail>(spC_PlugNet);
	return pC_SendMail;
}

void ReleaseC_SendMail(I_SendMail* pI_SendMail) {
	D_OutInfo();
	C_SendMail* pC_SendMail = static_cast<C_SendMail*>(pI_SendMail);
	Delete(pC_SendMail);
}

C_SendMail::T_SPC_SendMail C_SendMail::NewC_SendMail(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto pC_SendMail = CreateC_SendMail(spC_PlugNet);
	auto spC_SendMail = C_SendMail::T_SPC_SendMail(pC_SendMail, ReleaseC_SendMail);
	return spC_SendMail;
}

C_SendMail::T_SPI_SendMail C_SendMail::NewI_SendMail(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto spC_SendMail = C_SendMail::NewC_SendMail(spC_PlugNet);
	auto spI_SendMail = spC_SendMail->GetSPI_SendMail();
	return spI_SendMail;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif