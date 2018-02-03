#pragma once

#include <bsn_cpp/plug_net/include/i_plug_net.h>


#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_net.h>


#include <boost/function.hpp>
#include <boost/asio.hpp>

#include <stdint.h>
#include <memory>
#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class I_TCPSession : public std::enable_shared_from_this<I_TCPSession> {
public:
	typedef std::shared_ptr<I_TCPSession> T_SPI_TCPSession;
	typedef boost::asio::ip::tcp::socket T_Socket;

public:
	T_Socket& GetSocket() { return m_Socket; }

public:
	T_SPI_TCPSession GetSPI_TCPSession() {
		D_OutInfo();
		return shared_from_this();
	}

public:
	I_TCPSession(I_PlugNet::T_SPI_PlugNet spI_PlugNet)
		: m_spI_PlugNet(spI_PlugNet)
		, m_Socket(spI_PlugNet->GetSPI_PlugMgr()->GetIOService()) {

	}
	virtual ~I_TCPSession() = default;

protected:
	I_PlugNet::T_SPI_PlugNet m_spI_PlugNet;
	T_Socket m_Socket;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End