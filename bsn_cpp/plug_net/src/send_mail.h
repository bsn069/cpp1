#pragma once

#include <bsn_cpp/plug_net/include/i_send_mail.h>
#include <bsn_cpp/plug_net/src/plug_net.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_SendMail : public I_SendMail {
public:
	typedef std::shared_ptr<C_SendMail> T_SPC_SendMail;	

public: // I_SendMail
	void SendTest();

public:
	static T_SPC_SendMail NewC_SendMail(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	static T_SPI_SendMail NewI_SendMail(C_PlugNet::T_SPC_PlugNet spC_PlugNet);

	T_SPC_SendMail GetSPC_SendMail();
	void SendTestSyncImp();

	void SendMailCoro(boost::asio::yield_context yield);
	
	void ConnectCoro(boost::asio::yield_context yield);
	void LoginCoro(boost::asio::yield_context yield);
	void SendCoro(boost::asio::yield_context yield);

	void Cmd(
		boost::asio::yield_context yield
		, std::string const& strSend
		, uint32_t& u32RetCode
	);

public:
	C_SendMail(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	virtual ~C_SendMail();

public:
	C_PlugNet::T_SPC_PlugNet m_spC_PlugNet;
	boost::asio::ip::tcp::socket m_Socket;

	std::string m_strSmtpHost;
	uint16_t m_u16Port;

	std::string m_strUserBase64;
	std::string m_strPwdBase64;

	bool m_bHadConnect;
	bool m_bHadLogin;

	bool m_bSending;
	std::string m_strMailFrom;
	std::string m_strMailTo;
	std::string m_strMailSubject;
	std::string m_strMailContent;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End