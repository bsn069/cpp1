#pragma once

#include <bsn_cpp/plug_client/src/plug_client.h>
#include <bsn_cpp/plug_net/include/i_address.h>

#include <boost/function.hpp>

#include <map>
#include <memory>

D_BsnNamespace1(plug_client)
//////////////////////////////////////////////////////////////////////
class C_Gate : public std::enable_shared_from_this<C_Gate>  {
public:
	typedef std::shared_ptr<C_Gate> T_SPC_Gate;	
	typedef C_PlugClient::T_SPI_TCPSession T_SPI_TCPSession;
	typedef D_N1(plug_net)::I_Address::T_SPI_Address T_SPI_Address;

public:
	static T_SPC_Gate NewC_Gate(C_PlugClient::T_SPC_PlugClient spC_PlugClient);

	T_SPC_Gate GetSPC_Gate();

	bool Start();
	bool Connect();
	void OnConnect(T_SPI_TCPSession spI_TCPSession);
	bool Send(uint8_t const* pData, uint16_t uLen);

public:
	C_Gate(C_PlugClient::T_SPC_PlugClient spC_PlugClient);
	~C_Gate();

public:
	C_PlugClient::T_SPC_PlugClient 	m_spC_PlugClient;
	T_SPI_TCPSession m_spI_TCPSession;
	T_SPI_Address m_spI_Address;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End