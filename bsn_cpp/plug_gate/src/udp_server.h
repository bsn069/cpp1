// #pragma once

// #include <bsn_cpp/plug_net/include/i_address.h>

// #include <bsn_cpp/include/name_space.h>

// #include <boost/asio.hpp>
// #include <boost/asio/spawn.hpp>

// #include <vector>
// #include <string>

// D_BsnNamespace1(plug_gate)
// //////////////////////////////////////////////////////////////////////
// class C_PlugGate;

// class C_UDPServer : public std::enable_shared_from_this<C_UDPServer> {
// public:
// 	typedef std::shared_ptr<C_UDPServer>    T_SPC_UDPServer;	
// 	typedef std::shared_ptr<C_PlugGate>     T_SPC_PlugGate;	
// 	typedef boost::asio::ip::udp::socket    T_Socket;
// 	typedef D_N1(plug_net)::I_Address::T_SPI_Address T_SPI_Address;
//     typedef boost::asio::ip::udp::endpoint  T_EndPoint;

// public:
// 	static T_SPC_UDPServer NewC_UDPServer(C_UDPServer::T_SPC_PlugGate spC_PlugGate, C_UDPServer::T_SPI_Address spI_Address);
 
//  	C_UDPServer::T_SPC_UDPServer    GetSPC_UDPServer();
// 	C_UDPServer::T_Socket&          GetSocket();
// 	C_UDPServer::T_SPI_Address      GetAddress();

//     bool Start();
// 	bool Stop();

// public:
// 	C_UDPServer(C_UDPServer::T_SPC_PlugGate spC_PlugGate, C_UDPServer::T_SPI_Address spI_Address);
// 	~C_UDPServer();

// public:
// 	C_UDPServer::T_SPC_PlugGate m_spC_PlugGate;
// 	C_UDPServer::T_SPI_Address  m_spI_Address;
// 	C_UDPServer::T_Socket       m_Socket;
//     T_EndPoint                  m_remoteEndPoint;

// private:
// 	void RunCoroutineImp(boost::asio::yield_context yield);
// };
// //////////////////////////////////////////////////////////////////////
// D_BsnNamespace1End