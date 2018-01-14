#include <bsn_cpp/plug_net/src/url.h>
 
#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <iostream>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
C_URL::C_URL(C_PlugNet::T_SPC_PlugNet spC_PlugNet) 
	: m_spC_PlugNet(spC_PlugNet) {
	D_OutInfo();
}

C_URL::~C_URL() {
	D_OutInfo();
 
}

C_URL::T_SPC_URL C_URL::GetSPC_URL() {
	D_OutInfo();
	auto spI_URL = GetSPI_URL();
	auto spC_URL = std::dynamic_pointer_cast<C_URL>(spI_URL);
	return spC_URL;
}

std::string const& C_URL::GetHost() {
	return m_strHost;
}

std::string const& C_URL::GetPath() {
	return m_strPath;
}

std::string const& C_URL::GetProto() {
	return m_strProto;
}

std::string const& C_URL::GetURL() {
	return m_strURL;
}

uint16_t C_URL::GetPort() {
	return m_u16Port;
}


void C_URL::Parse(std::string const& strURL) {
	D_OutInfo1(strURL);

	std::size_t beginIndex;
	if (strURL.compare(0, 7, "http://") == 0) {
		m_strProto = "http";
		beginIndex = 7;
		m_u16Port = 80;
	} else if (strURL.compare(0, 8, "https://") == 0) {
		m_strProto = "https";
		beginIndex = 8;
		m_u16Port = 443;
	} else {
		D_OutInfo1("must begin http:// or https://");
		return;
	}
	m_strURL = strURL;

	auto pos = m_strURL.find_first_of('/', beginIndex);
	if (pos == std::string::npos) {
		m_strHost	= m_strURL.substr(beginIndex);
		m_strPath	= "/";
	} else {
		m_strHost	= m_strURL.substr(beginIndex, pos-beginIndex);
		m_strPath = m_strURL.substr(pos);
	}

	D_OutInfo2("proto:", m_strProto);
	D_OutInfo2("host:", m_strHost);
	D_OutInfo2("port:", m_u16Port);
	D_OutInfo2("path:", m_strPath);
}


//////////////////////////////////////////////////////////////////////
C_URL* CreateC_URL(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	C_URL* pC_URL = New<C_URL>(spC_PlugNet);
	return pC_URL;
}

void ReleaseC_URL(I_URL* pI_URL) {
	D_OutInfo();
	C_URL* pC_URL = static_cast<C_URL*>(pI_URL);
	Delete(pC_URL);
}

C_URL::T_SPC_URL C_URL::NewC_URL(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto pC_URL = CreateC_URL(spC_PlugNet);
	auto spC_URL = C_URL::T_SPC_URL(pC_URL, ReleaseC_URL);
	return spC_URL;
}

C_URL::T_SPI_URL C_URL::NewI_URL(C_PlugNet::T_SPC_PlugNet spC_PlugNet) {
	D_OutInfo();
	auto spC_URL = C_URL::NewC_URL(spC_PlugNet);
	auto spI_URL = spC_URL->GetSPI_URL();
	return spI_URL;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif