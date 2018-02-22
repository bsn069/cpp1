#pragma once

#include <bsn_cpp/plug_net/include/i_tcp_listen.h>
#include <bsn_cpp/plug_net/src/plug_net.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>
#include <boost/asio/spawn.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_TCPListen : public I_TCPListen {
public:
	typedef std::shared_ptr<C_TCPListen> T_SPC_TCPListen;	

public: // I_TCPListen
	virtual I_Address::T_SPI_Address GetAddress() override;
	virtual bool SetAddress(I_Address::T_SPI_Address spI_Address) override;

	virtual bool StartListen() override;
	virtual bool StopListen() override;
    virtual bool InListen() override;

	virtual void SetFuncNew(T_FuncNew func) override;
	virtual void SetFuncOnAccept(T_FuncOnAccept func) override;
	
public:
	static T_SPC_TCPListen NewC_TCPListen(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	static T_SPI_TCPListen NewI_TCPListen(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
 
 	T_SPC_TCPListen GetSPC_TCPListen();

	void ListenCoro(boost::asio::yield_context yield);
	bool CanListen();

public:
	C_TCPListen(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	virtual ~C_TCPListen();

public:
	C_PlugNet::T_SPC_PlugNet m_spC_PlugNet;
	boost::asio::io_service& m_IOService;
	boost::asio::ip::tcp::acceptor m_Acceptor;

	I_Address::T_SPI_Address m_spI_Address;

	bool m_bListen;

	T_FuncNew m_FuncNew;
	T_FuncOnAccept m_FuncOnAccept;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End