#include <bsn_cpp/plug_net/src/dns.h>
 
#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_Dns::C_Dns(C_PlugNet::T_SPC_PlugNet spC_PlugNet) 
	: m_spC_PlugNet(spC_PlugNet) {
	D_OutInfo();
}

C_Dns::~C_Dns() {
	D_OutInfo();
 
}

C_Dns::T_SPC_Dns C_Dns::GetSPC_Dns() {
	D_OutInfo();
	auto spI_Dns = GetSPI_Dns();
	auto spC_Dns = std::dynamic_pointer_cast<C_Dns>(spI_Dns);
	return spC_Dns;
}

std::vector<std::string> C_Dns::Domain2IPs(std::string const& strDomain) {
	std::cout << "[" << strDomain << "]" << std::endl;
    boost::asio::ip::tcp::resolver::query qry(strDomain, "0");
    boost::asio::ip::tcp::resolver::iterator it = m_spC_PlugNet->m_pData->m_Resolver.resolve(qry);  
    boost::asio::ip::tcp::resolver::iterator end;  
    std::vector<std::string> vecIPs;  
    for (; it != end; it++) {  
        vecIPs.push_back((*it).endpoint().address().to_string());  
    }  
    return vecIPs;  
}

void C_Dns::Domain2IPs_async(std::string const& strDomain, T_DnsAsyncCB cb) {
	D_OutInfo1(strDomain);
    boost::asio::ip::tcp::resolver::query qry(strDomain, "0");
    m_spC_PlugNet->m_pData->m_Resolver.async_resolve(qry, boost::bind(&D_N1(plug_mgr)::C_PlugDataNet::Domain2IPs_async_handle, m_spC_PlugNet->m_pData, _1, _2, strDomain, cb));  
}

// std::string C_Dns::GetRequest(std::string url) {  
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

// std::string C_Dns::GetRequest(char* host, char* path) {  
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
C_Dns* CreateC_Dns(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	C_Dns* pC_Dns = New<C_Dns>(spC_PlugNet);
	return pC_Dns;
}

void ReleaseC_Dns(I_Dns* pI_Dns) {
	D_OutInfo();
	C_Dns* pC_Dns = static_cast<C_Dns*>(pI_Dns);
	Delete(pC_Dns);
}

C_Dns::T_SPC_Dns C_Dns::NewC_Dns(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto pC_Dns = CreateC_Dns(spC_PlugNet);
	auto spC_Dns = C_Dns::T_SPC_Dns(pC_Dns, ReleaseC_Dns);
	return spC_Dns;
}

C_Dns::T_SPI_Dns C_Dns::NewI_Dns(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto spC_Dns = C_Dns::NewC_Dns(spC_PlugNet);
	auto spI_Dns = spC_Dns->GetSPI_Dns();
	return spI_Dns;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif