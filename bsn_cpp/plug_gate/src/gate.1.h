// #pragma once

// #include <bsn_cpp/plug_gate/src/udp_server.h>

// #include <bsn_cpp/plug_mgr/include/i_plug.h>
// #include <bsn_cpp/plug_net/include/i_tcp_listen.h>
// #include <bsn_cpp/plug_net/include/i_tcp_session.h>
// #include <bsn_cpp/plug_net/include/i_plug_net.h>

// #include <boost/function.hpp>

// #include <map>
// #include <memory>

// D_BsnNamespace1(plug_gate)
// //////////////////////////////////////////////////////////////////////
// class C_Gate : public std::enable_shared_from_this<C_Gate> {
// public:
// 	typedef std::shared_ptr<C_Gate> T_SPC_Gate;	
// 	typedef D_N1(plug_net)::I_TCPListen::T_SPI_TCPListen T_SPI_TCPListen;
// 	typedef D_N1(plug_net)::I_TCPSession::T_SPI_TCPSession T_SPI_TCPSession;
// 	typedef std::set<T_SPI_TCPSession> T_Sessions;

// public:
// 	static T_SPC_Gate NewC_Gate(void* pData);
// 	static T_SPI_Gate NewI_Gate(void* pData);

//     bool InitNeedPlug();
//     bool ClearNeedPlug();

// 	T_SPC_Gate GetSPC_Gate();
// 	bool RegAllCmd();
// 	bool StartClientTCPListen();
// 	bool StartClientUDPListen();

// 	T_SPI_TCPSession FuncNew();
// 	void FuncOnAccept(T_SPI_TCPSession spI_TCPSession);

// public:  
// 	void CmdHelp(bool bShowHelp, std::string const& strParam);

// public:
// 	C_Gate(void* pData);
// 	virtual ~C_Gate();

// public:
// 	T_SPI_PlugMgr 	m_spI_PlugMgr;
// 	T_SPI_TCPListen m_spI_TCPListen;
// 	T_Sessions		m_clientSessions;
//     C_UDPServer::T_SPC_UDPServer m_spC_UDPServer;

//     T_SPI_PlugNet m_spI_PlugNet;
//     T_SPI_PlugCmd m_spI_PlugCmd;
// };
// //////////////////////////////////////////////////////////////////////
// D_BsnNamespace1End