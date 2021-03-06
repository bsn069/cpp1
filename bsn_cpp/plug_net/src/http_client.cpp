#include <bsn_cpp/plug_net/src/http_client.h>
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
C_HttpClient::C_HttpClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet) 
	: m_spC_PlugNet(spC_PlugNet) {
	D_OutInfo();
}

C_HttpClient::~C_HttpClient() {
	D_OutInfo();
 
}

C_HttpClient::T_SPC_HttpClient C_HttpClient::GetSPC_HttpClient() {
	D_OutInfo();
	auto spI_HttpClient = GetSPI_HttpClient();
	auto spC_HttpClient = std::dynamic_pointer_cast<C_HttpClient>(spI_HttpClient);
	return spC_HttpClient;
}

void C_HttpClient::Get_async(std::string const& strURL, T_HttpClientAsyncCB cb) {

	auto spC_URL = C_URL::NewC_URL(m_spC_PlugNet);
	spC_URL->Parse(strURL);

	auto self = GetSPC_HttpClient();
	boost::asio::ip::tcp::resolver::query qry(spC_URL->GetHost(), boost::lexical_cast<std::string>(spC_URL->GetPort()));
    m_spC_PlugNet->m_pData->m_Resolver.async_resolve(
		qry
		, [spC_URL, self](boost::system::error_code const& ec, boost::asio::ip::tcp::resolver::iterator i) {
			if (ec) {
				D_OutInfo1(ec);
				return;
			}
			D_OutInfo1((*i).endpoint().address().to_string());

			auto pSocket = new boost::asio::ip::tcp::socket(self->m_spC_PlugNet->m_pData->m_ioService);  
			auto Socket = std::shared_ptr<boost::asio::ip::tcp::socket>(pSocket);

			boost::asio::ip::tcp::resolver::iterator end;
			boost::asio::async_connect(
				*Socket
				, i
				, [spC_URL, self, Socket](boost::system::error_code const& ec, boost::asio::ip::tcp::resolver::iterator i){
					if (ec) {
						D_OutInfo1(ec);
						D_OutInfo1(boost::system::system_error(ec).what());   
						return;
					}
					boost::asio::streambuf request;  
					std::ostream request_stream(&request);  
					request_stream << "GET " << spC_URL->GetPath() << " HTTP/1.1\r\n";  
					request_stream << "Host: " << spC_URL->GetHost() << "\r\n";  
					request_stream << "Accept: */*\r\n";  
					request_stream << "Connection: close\r\n\r\n"; 

					boost::asio::async_write(*Socket
						, request
						, boost::asio::transfer_all()
						, [self, Socket](boost::system::error_code ec, std::size_t st){
							D_OutInfo1(st);
							if (ec) {
								D_OutInfo1(ec);
								D_OutInfo1(boost::system::system_error(ec).what());   
								return;
							}

							auto pRes = new boost::asio::streambuf();
							auto Res = std::shared_ptr<boost::asio::streambuf>(pRes);
							boost::asio::streambuf response;  
							boost::asio::async_read(*Socket
								, *Res
								, boost::asio::transfer_all()
								, [self, Socket, Res](boost::system::error_code ec, std::size_t st){
									D_OutInfo1(st);
									if (ec && ec != boost::asio::error::eof) {
										D_OutInfo1(ec);
										D_OutInfo1(boost::system::system_error(ec).what());   
										return;
									}
									std::istream is(Res.get());  
									is.unsetf(std::ios_base::skipws);  
									std::string sz;  
									sz.append(std::istream_iterator<char>(is), std::istream_iterator<char>());  
									D_OutInfo1(sz);
								}
							);
						}
					); 
				}
			);
		}
	);
}


void C_HttpClient::GetCoroutine(std::string const& strURL) {
    boost::asio::spawn(m_spC_PlugNet->m_pData->m_ioService,
        boost::bind(&C_HttpClient::GetCoroutineImp,
          GetSPC_HttpClient(), strURL, _1));
}

void C_HttpClient::GetCoroutineImp(std::string strURL, boost::asio::yield_context yield) {
	boost::system::error_code ec; 

	auto spC_URL = C_URL::NewC_URL(m_spC_PlugNet);
	spC_URL->Parse(strURL);

	boost::asio::ip::tcp::resolver::query qry(spC_URL->GetHost(), boost::lexical_cast<std::string>(spC_URL->GetPort()));
	boost::asio::ip::tcp::resolver 	rsv(m_spC_PlugNet->m_pData->m_ioService);
	auto endpoint_iterator = rsv.async_resolve(qry, yield[ec]);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 

	auto Socket = boost::asio::ip::tcp::socket(m_spC_PlugNet->m_pData->m_ioService);
	
	boost::asio::async_connect(Socket, endpoint_iterator, yield[ec]);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 

	boost::asio::streambuf request;  
	std::ostream request_stream(&request);  
	request_stream << "GET " << spC_URL->GetPath() << " HTTP/1.1\r\n";  
	request_stream << "Host: " << spC_URL->GetHost() << "\r\n";  
	request_stream << "Accept: */*\r\n";  
	request_stream << "Connection: close\r\n\r\n"; 

	boost::asio::async_write(Socket, request, boost::asio::transfer_all(), yield[ec]);
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 

	boost::asio::streambuf response;  
	boost::asio::async_read(
		Socket
		, response
		, boost::asio::transfer_all()
		, yield[ec]
	);
	if (ec && ec != boost::asio::error::eof) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return;
	} 

	std::istream is(&response);  
	is.unsetf(std::ios_base::skipws);  
	std::string sz;  
	sz.append(std::istream_iterator<char>(is), std::istream_iterator<char>());  
	D_OutInfo1(sz);
}

std::string C_HttpClient::Get(std::string const& strURL) {
	std::string strRet;

	auto spC_URL = C_URL::NewC_URL(m_spC_PlugNet);
	spC_URL->Parse(strURL);

	auto spC_Dns = C_Dns::NewC_Dns(m_spC_PlugNet);
	auto vecIPs = spC_Dns->Domain2IPs(spC_URL->GetHost());
	if (vecIPs.empty()) {
		D_OutInfo2("not found ip", spC_URL->GetHost());
		return "";
	}


	boost::asio::ip::tcp::socket Socket(m_spC_PlugNet->m_pData->m_ioService);  
	boost::system::error_code ec; 
	for (auto strIP : vecIPs) {
		boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::from_string(strIP), spC_URL->GetPort());
		Socket.connect(ep, ec);     
        if (ec) {  
			continue;
        }   
		break; 
	}
	if (ec) {  
		D_OutInfo1(boost::system::system_error(ec).what());   
		return "";
	} 

	boost::asio::streambuf request;  
    std::ostream request_stream(&request);  
    request_stream << "GET " << spC_URL->GetPath() << " HTTP/1.1\r\n";  
    request_stream << "Host: " << spC_URL->GetHost() << "\r\n";  
    request_stream << "Accept: */*\r\n";  
    request_stream << "Connection: close\r\n\r\n";  
      
    boost::asio::write(Socket, request);  

	boost::asio::streambuf response;  

    boost::system::error_code error;  // 读取错误  
    while (boost::asio::read(Socket, response, boost::asio::transfer_at_least(1), error)) {  
        auto size = response.size();  
		D_OutInfo1(size);
    }  
  
    if (error != boost::asio::error::eof) {  
		D_OutInfo1(error);
    }  

    std::istream is(&response);  
    is.unsetf(std::ios_base::skipws);  
    std::string sz;  
    sz.append(std::istream_iterator<char>(is), std::istream_iterator<char>());  
	D_OutInfo1(sz);
    
	return strRet;
}


// std::string C_HttpClient::GetRequest(std::string url) {  
//     size_t index;  
      
//     // 去掉url中的协议头  
//     if (url.find("http://") != string::npos ) {  
//         url = url.substr(7);  
//     }  
//     printf("url:%s\n", url.c_str());  
      
//     // 截取host字符串  
//     index = url.find("/");  
//     char* host = new char[index];  
//     strcpy(host, url.substr(0, index).c_str());  
      
//     // 截取urlPath字符串  
//     char* urlPath = new char[url.length() - index + 1];  
//     strcpy(urlPath, url.substr(index, url.length() - index).c_str());  
      
//     return GetRequest(host, urlPath);  
// }  

// std::string C_HttpClient::GetRequest(char* host, char* path) {  
//     boost::asio::tcp::resolver resolver(m_ioService);  
//     boost::asio::tcp::resolver::query query(host,"http");  
//     boost::asio::tcp::resolver::iterator iter = resolver.resolve(query);  
  
//     // 尝试连接每一个终端，直到成功建立socket连接  
//     boost::asio::tcp::socket socket(m_ioService);  
//     boost::asio::connect(socket, iter);  
      
//     // 构建网络请求头.  
//     // 指定 "Connection: close" 在获取应答后断开连接，确保获文件全部数据。  
//     boost::asio::streambuf request;  
//     ostream request_stream(&request);  
//     request_stream << "GET " << path << " HTTP/1.1\r\n";  
//     request_stream << "Host: " << host << "\r\n";  
//     request_stream << "Accept: */*\r\n";  
//     request_stream << "Connection: close\r\n\r\n";  
      
//     // 发送请求  
//     boost::asio::write(socket, request);  
      
//     // 读取应答状态. 应答缓冲流 streambuf 会自动增长至完整的行  
//     // 该增长可以在构造缓冲流时通过设置最大值限制  
//     boost::asio::streambuf response;  
//     boost::asio::read_until(socket, response, "\r\n");  
      
//     // 检查应答是否OK.  
//     istream response_stream(&response);  
//     string http_version;  
//     response_stream >> http_version;  
//     unsigned int status_code;  
//     response_stream >> status_code;  
//     string status_message;  
//     getline(response_stream, status_message);  
//     if (!response_stream || http_version.substr(0, 5) != "HTTP/")  
//     {  
//         printf("响应无效\n");  
//     }  
//     if (status_code != 200)  
//     {  
//         printf("响应返回 status code %d\n", status_code);  
//     }  
      
//     // 读取应答头部，遇到空行后停止  
//     boost::asio::read_until(socket, response, "\r\n\r\n");  
      
//     // 显示应答头部  
      
//     string header;  
//     int len = 0;  
//     while (getline(response_stream, header) && header != "\r")  
//     {  
//         if (header.find("Content-Length: ") == 0) {  
//             stringstream stream;  
//             stream << header.substr(16);  
//             stream >> len;  
//         }  
//     }  
      
//     long size = response.size();  
  
//     if (size > 0) {  
//         // ... do nothing ...  
//     }  
      
//     boost::system::error_code error;  // 读取错误  
      
//     // 循环读取数据流，直到文件结束  
//     while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))  
//     {  
//         // 获取应答长度  
//         size = response.size();  
//         if (len != 0) {  
//             cout << size << "  Byte  " << (size * 100) / len << "%" << endl;  
//         }  
//     }  
  
//     // 如果没有读到文件尾，抛出异常  
//     if (error != boost::asio::error::eof)  
//     {  
//         throw boost::system::system_error(error);  
//     }  
      
//     cout << size << " Byte 内容已下载完毕." << endl;  
      
//     // 将streambuf类型转换为string类型，并返回  
//     istream is(&response);  
//     is.unsetf(ios_base::skipws);  
//     string sz;  
//     sz.append(istream_iterator<char>(is), istream_iterator<char>());  
      
//     return sz;  
// }
//////////////////////////////////////////////////////////////////////
C_HttpClient* CreateC_HttpClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	C_HttpClient* pC_HttpClient = New<C_HttpClient>(spC_PlugNet);
	return pC_HttpClient;
}

void ReleaseC_HttpClient(I_HttpClient* pI_HttpClient) {
	D_OutInfo();
	C_HttpClient* pC_HttpClient = static_cast<C_HttpClient*>(pI_HttpClient);
	Delete(pC_HttpClient);
}

C_HttpClient::T_SPC_HttpClient C_HttpClient::NewC_HttpClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto pC_HttpClient = CreateC_HttpClient(spC_PlugNet);
	auto spC_HttpClient = C_HttpClient::T_SPC_HttpClient(pC_HttpClient, ReleaseC_HttpClient);
	return spC_HttpClient;
}

C_HttpClient::T_SPI_HttpClient C_HttpClient::NewI_HttpClient(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto spC_HttpClient = C_HttpClient::NewC_HttpClient(spC_PlugNet);
	auto spI_HttpClient = spC_HttpClient->GetSPI_HttpClient();
	return spI_HttpClient;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif