// #include <bsn_cpp/plug_gate/src/udp_server.h>
// #include <bsn_cpp/plug_gate/src/plug_gate.h>
 
// #include <bsn_cpp/include/d_out.h>
// #include <bsn_cpp/include/new.hpp>
// #include <bsn_cpp/include/delete.hpp>

// #include <boost/bind.hpp>
// #include <boost/asio.hpp>

// using namespace boost::asio::ip;

// D_BsnNamespace1(plug_gate)
// //////////////////////////////////////////////////////////////////////
// C_UDPServer::C_UDPServer(C_PlugGate::T_SPC_PlugGate spC_PlugGate, C_UDPServer::T_SPI_Address spI_Address)
// 	: m_spC_PlugGate(spC_PlugGate)
//     , m_spI_Address(spI_Address)
// 	, m_Socket(
//         spC_PlugGate->GetSPI_PlugMgr()->GetIOService()
//         , udp::endpoint(address::from_string(spI_Address->GetAddr()), spI_Address->GetPort())
//     ) {

// };

// C_UDPServer::~C_UDPServer() {
// 	D_OutInfo();
// 	m_spC_PlugGate = nullptr;
//     m_spI_Address = nullptr;    
// }

// C_UDPServer::T_SPC_UDPServer C_UDPServer::GetSPC_UDPServer() {
//     D_OutInfo();
//     return shared_from_this();
// }
 

// C_UDPServer::T_SPI_Address C_UDPServer::GetAddress() {
//     return m_spI_Address;
// }

// bool C_UDPServer::Start() {
// 	D_OutInfo();
//     boost::asio::spawn(
// 		m_spC_PlugGate->GetSPI_PlugMgr()->GetIOService()
// 		, boost::bind(
// 			&C_UDPServer::RunCoroutineImp
// 			, GetSPC_UDPServer()
// 			, _1
// 		)
// 	);
// 	return true;	
// }

// bool C_UDPServer::Stop() {
// 	D_OutInfo();

//     m_Socket.cancel();
//     m_Socket.close();

//     return true;
// }

// void C_UDPServer::RunCoroutineImp(boost::asio::yield_context yield) {
// 	D_OutInfo();
// 	boost::system::error_code ec; 

// 	auto yield_ec = yield[ec];
// 	while (true) {
// 		auto bytes_transferred = m_Socket.async_receive_from(
// 			boost::asio::buffer(m_Buffer)
//             , m_remoteEndPoint
// 			, yield_ec
// 		);
// 		if (ec) {  
// 			D_OutInfo1(boost::system::system_error(ec).what());  
// 			break;
// 		} 
// 		std::string strInfo(m_Buffer.data(), bytes_transferred);
// 		D_OutInfo2(bytes_transferred, strInfo);
// 	}
// }
 
// //////////////////////////////////////////////////////////////////////
// C_UDPServer* CreateC_UDPServer(C_PlugGate::T_SPC_PlugGate spC_PlugGate, C_UDPServer::T_SPI_Address spI_Address) {
// 	D_OutInfo();
// 	C_UDPServer* pC_UDPServer = New<C_UDPServer>(spC_PlugGate, spI_Address);
// 	return pC_UDPServer;
// }

// void ReleaseC_UDPServer(C_UDPServer* pC_UDPServer) {
// 	D_OutInfo();
// 	Delete(pC_UDPServer);
// }

// C_UDPServer::T_SPC_UDPServer C_UDPServer::NewC_UDPServer(C_PlugGate::T_SPC_PlugGate spC_PlugGate, C_UDPServer::T_SPI_Address spI_Address) {
// 	D_OutInfo();
// 	auto pC_UDPServer = CreateC_UDPServer(spC_PlugGate, spI_Address);
// 	auto spC_UDPServer = C_UDPServer::T_SPC_UDPServer(pC_UDPServer, ReleaseC_UDPServer);
// 	return spC_UDPServer;
// }
 
// //////////////////////////////////////////////////////////////////////
// D_BsnNamespace1End
 