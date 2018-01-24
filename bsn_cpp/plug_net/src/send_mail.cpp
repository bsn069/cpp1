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

#include <iostream>

using boost::asio::ip;

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_SendMail::C_SendMail(C_PlugNet::T_SPC_PlugNet spC_PlugNet) 
	: m_spC_PlugNet(spC_PlugNet)
	, m_Socket(spC_PlugNet->GetIOService()) {
	D_OutInfo();
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

void C_SendMail::SpawnCoroutine() {
	D_OutInfo();
    boost::asio::spawn(m_spC_PlugNet->GetIOService(),
        boost::bind(&C_SendMail::CoroutineImp,
          GetSPC_SendMail(), _1));
}

void C_SendMail::CoroutineImp(boost::asio::yield_context yield) {
	D_OutInfo();
	boost::system::error_code ec; 
 
}
 
void C_SendMail::SendTest() {
	D_OutInfo();

	// SendTestSyncImp();
    // boost::asio::spawn(m_spC_PlugNet->GetIOService(),
    //     boost::bind(&C_SendMail::SendTestCoroutineImp,
    //       GetSPC_SendMail(), _1));
    boost::asio::spawn(m_spC_PlugNet->GetIOService(),
        boost::bind(&C_SendMail::SendCoro,
          GetSPC_SendMail(), _1));
}

void C_SendMail::SendCoro(boost::asio::yield_context yield) {
	D_OutInfo();
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

	char reply[1024];
	size_t reply_length = 0;

	boost::asio::streambuf response;  
	reply_length = boost::asio::async_read_until(
		m_Socket
		, boost::asio::buffer(reply)
		, "\n"
		, yield[ec]
	);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 
    reply[reply_length] = '\0';
	D_OutInfo2("read success", reply);
}

void C_SendMail::SendTestSyncImp() {
	D_OutInfo();
	boost::system::error_code ec; 

	auto spC_Dns = C_Dns::NewC_Dns(m_spC_PlugNet);
	auto vecIPs = spC_Dns->Domain2IPs("smtp.163.com");
	if (vecIPs.empty()) {
		D_OutInfo2("not found ip", "smtp.163.com");
		return;
	}

	auto Socket = boost::asio::ip::tcp::socket(m_spC_PlugNet->GetIOService());
	for (auto strIP : vecIPs) {
		D_OutInfo1(strIP);
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::from_string(strIP), 25);
		Socket.connect(ep, ec);     
        if (ec) {  
			D_OutInfo1(boost::system::system_error(ec).what());   
			continue;
        }   
		break; 
	}
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 
	D_OutInfo1("connect success");

	char reply[1024];
	size_t reply_length = 0;

	reply_length = Socket.read_some(boost::asio::buffer(reply), ec);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 
    std::cout << "Reply is: ";
    std::cout.write(reply, reply_length);
    std::cout << "\n";

	std::string strData;
	
	{
		std::cout << "Reply is: ";
		
		strData = "helo ceshi\r\nauth login\r\n";
		boost::asio::write(Socket, boost::asio::buffer(strData.data(), strData.size()), ec); 
		reply_length = Socket.read_some(boost::asio::buffer(reply),  ec);
		std::cout.write(reply, reply_length);

		// strData = "auth login\r\n";
		// boost::asio::write(Socket, boost::asio::buffer(strData.data(), strData.size()), ec); 
		// reply_length = Socket.read_some(boost::asio::buffer(reply),  ec);
		// std::cout.write(reply, reply_length);

		// strData = "YnNuXzE2M0AxNjMuY29t\r\n";
		// boost::asio::write(Socket, boost::asio::buffer(strData.data(), strData.size()), ec); 
		// reply_length = Socket.read_some(boost::asio::buffer(reply),  ec);
		// std::cout.write(reply, reply_length);

		strData = "YnNuXzE2M0AxNjMuY29t\r\nWG8zSjJwMDQwTXVz\r\n";
		boost::asio::write(Socket, boost::asio::buffer(strData.data(), strData.size()), ec); 
		reply_length = Socket.read_some(boost::asio::buffer(reply),  ec);
		std::cout.write(reply, reply_length);

		// strData = "mail from:<bsn_163@163.com>\r\nrcpt to:<15914057651@139.com>\r\n";
		// boost::asio::write(Socket, boost::asio::buffer(strData.data(), strData.size()), ec); 
		// reply_length = Socket.read_some(boost::asio::buffer(reply),  ec);
		// std::cout.write(reply, reply_length);

		strData = "mail from:<bsn_163@163.com>\r\nrcpt to:<15914057651@139.com>\r\ndata\r\nFrom:bsn_163@163.com\r\nTo:15914057651@139.com\r\nSubject:butao\r\n\r\nfriend1\r\n.\r\n";
		boost::asio::write(Socket, boost::asio::buffer(strData.data(), strData.size()), ec); 
		boost::this_thread::sleep_for(boost::chrono::seconds(2));
		
		reply_length = Socket.read_some(boost::asio::buffer(reply),  ec);
		std::cout.write(reply, reply_length);

		std::cout << "\n";
	}	

	// {
	// 	strData = "helo ceshi\r\nauth login\r\n";
	// 	D_OutInfo1(strData);
	// 	boost::asio::write(Socket, boost::asio::buffer(strData.data(), strData.size()), ec); 
	// 	if (ec) {  
	// 		D_OutInfo1(boost::system::system_error(ec).what());   
	// 		return;
	// 	} 

	// 	// boost::this_thread::sleep_for(boost::chrono::seconds(1));
	// 	while (true) {
	// 		reply_length = Socket.read_some(boost::asio::buffer(reply),  ec);
	// 		if (ec) {  
	// 			if (ec == boost::asio::error::eof) {
	// 				D_OutInfo1(ec);   
	// 			}
	// 			D_OutInfo1(boost::system::system_error(ec).what());   
	// 			break;
	// 		} 
	// 		std::cout << "Reply is: ";
	// 		std::cout.write(reply, reply_length);
	// 		std::cout << "\n";
	// 		break;
	// 	}
	// }
	// {
	// 	strData = "YnNuXzE2M0AxNjMuY29t\r\nWG8zSjJwMDQwTXVz\r\n";
	// 	D_OutInfo1(strData);
	// 	boost::asio::write(Socket, boost::asio::buffer(strData.data(), strData.size()), ec); 
	// 	if (ec) {  
	// 		D_OutInfo1(boost::system::system_error(ec).what());   
	// 		return;
	// 	} 

	// 	// boost::this_thread::sleep_for(boost::chrono::seconds(1));
	// 	while (true) {
	// 		reply_length = Socket.read_some(boost::asio::buffer(reply),  ec);
	// 		if (ec) {  
	// 			if (ec == boost::asio::error::eof) {
	// 				D_OutInfo1(ec);   
	// 			}
	// 			D_OutInfo1(boost::system::system_error(ec).what());   
	// 			break;
	// 		} 
	// 		std::cout << "Reply is: ";
	// 		std::cout.write(reply, reply_length);
	// 		std::cout << "\n";
	// 		break;
	// 	}
	// }
	// {
	// 	strData = "mail from:<bsn_163@163.com>\r\nrcpt to:<15914057651@139.com>\r\ndata\r\nFrom:bsn_163@163.com\r\nTo:15914057651@139.com\r\nSubject:butao\r\n\r\nfriend1\r\n.\r\n";
	// 	D_OutInfo1(strData);
	// 	boost::asio::write(Socket, boost::asio::buffer(strData.data(), strData.size()), ec); 
	// 	if (ec) {  
	// 		D_OutInfo1(boost::system::system_error(ec).what());   
	// 		return;
	// 	} 

	// 	// boost::this_thread::sleep_for(boost::chrono::seconds(1));
	// 	while (true) {
	// 		reply_length = Socket.read_some(boost::asio::buffer(reply),  ec);
	// 		if (ec) {  
	// 			if (ec == boost::asio::error::eof) {
	// 				D_OutInfo1(ec);   
	// 			}
	// 			D_OutInfo1(boost::system::system_error(ec).what());   
	// 			break;
	// 		} 
	// 		std::cout << "Reply is: ";
	// 		std::cout.write(reply, reply_length);
	// 		std::cout << "\n";
	// 		break;
	// 	}
	// }
}

void C_SendMail::SendTestCoroutineImp(boost::asio::yield_context yield) {
	D_OutInfo();
	boost::system::error_code ec; 

	boost::asio::ip::tcp::resolver::query qry("smtp.163.com", "25");
	boost::asio::ip::tcp::resolver 	rsv(m_spC_PlugNet->GetIOService());
	auto endpoint_iterator = rsv.async_resolve(qry, yield[ec]);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 
	D_OutInfo1("resolve success");

	auto Socket = boost::asio::ip::tcp::socket(m_spC_PlugNet->GetIOService());
	boost::asio::async_connect(Socket, endpoint_iterator, yield[ec]);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 
	D_OutInfo1("connect success");

	boost::asio::streambuf request;  
	std::ostream request_stream(&request);  
	request_stream << "helo s\n";  
	request_stream << "auth login\n";  
	request_stream << "YnNuXzE2M0AxNjMuY29t\n";  
	request_stream << "WG8zSjJwMDQwTXVz\n";  
	request_stream << "mail from:<bsn_163@163.com>\n";  
	request_stream << "rcpt to:<15914057651@139.com>\n";  
	request_stream << "data\n";  
	request_stream << "From:bsn_163@163.com\n";  
	request_stream << "To:15914057651@139.com\n";  
	request_stream << "Subject:butao";  
	request_stream << "\n\n";  
	request_stream << "friend1";  
	request_stream << "\n.\n";  
	// request_stream << "quit\r\n";  
 
	boost::asio::async_write(Socket, request, boost::asio::transfer_all(), yield[ec]);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 
	D_OutInfo1("write success");

	while (true) {
		boost::asio::streambuf response;  
		boost::asio::async_read_until(
			Socket
			, response
			, "\n"
			, yield[ec]
		);
		if (ec) {  
			D_OutInfo1(boost::system::system_error(ec).what());   
			return;
		} 
		D_OutInfo1("read success");

		std::istream is(&response);  
		is.unsetf(std::ios_base::skipws);  
		std::string sz;  
		sz.append(std::istream_iterator<char>(is), std::istream_iterator<char>());  
		D_OutInfo1(sz);
	}
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