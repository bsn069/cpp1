#pragma once

#include <bsn_cpp/plug_net/include/i_url.h>
#include <bsn_cpp/plug_net/src/plug_net.h>


#include <bsn_cpp/include/name_space.h>

#include <boost/asio.hpp>

#include <vector>
#include <string>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_URL : public I_URL {
public:
	typedef std::shared_ptr<C_URL> T_SPC_URL;	

public: // I_URL
	virtual void Parse(std::string const& strURL) override;
	virtual std::string const& GetHost() override;
	virtual std::string const& GetPath() override;
	virtual std::string const& GetProto() override;
	virtual std::string const& GetURL() override;
	virtual uint16_t GetPort() override;

public:
	static T_SPC_URL NewC_URL(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	static T_SPI_URL NewI_URL(C_PlugNet::T_SPC_PlugNet spC_PlugNet);

	T_SPC_URL GetSPC_URL();
	
public:
	C_URL(C_PlugNet::T_SPC_PlugNet spC_PlugNet);
	virtual ~C_URL();

public:
	C_PlugNet::T_SPC_PlugNet m_spC_PlugNet;
	std::string m_strURL;
	std::string m_strProto;
	std::string m_strHost;
	std::string m_strPath;
	uint16_t m_u16Port;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End