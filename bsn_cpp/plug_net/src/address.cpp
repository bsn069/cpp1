#include <bsn_cpp/plug_net/src/address.h>
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
C_Address::C_Address() 
	: m_u16Port(0) {
	D_OutInfo();
}

C_Address::~C_Address() {
	D_OutInfo();
 
}

void C_Address::SetAddr(std::string const& strAddr) {
	m_strAddr = strAddr;
}

void C_Address::SetPort(uint16_t u16Port) {
	m_u16Port = u16Port;
}

std::string const& C_Address::GetAddr() {
	return m_strAddr;
}

uint16_t C_Address::GetPort() {
	return m_u16Port;
}


C_Address::T_SPC_Address C_Address::GetSPC_Address() {
	D_OutInfo();
	auto spI_Address = GetSPI_Address();
	auto spC_Address = std::dynamic_pointer_cast<C_Address>(spI_Address);
	return spC_Address;
}
//////////////////////////////////////////////////////////////////////
C_Address* CreateC_Address() {
	D_OutInfo();
	C_Address* pC_Address = New<C_Address>();
	return pC_Address;
}

void ReleaseC_Address(I_Address* pI_Address) {
	D_OutInfo();
	C_Address* pC_Address = static_cast<C_Address*>(pI_Address);
	Delete(pC_Address);
}

C_Address::T_SPC_Address C_Address::NewC_Address() {
	D_OutInfo();
	auto pC_Address = CreateC_Address();
	auto spC_Address = C_Address::T_SPC_Address(pC_Address, ReleaseC_Address);
	return spC_Address;
}

C_Address::T_SPI_Address C_Address::NewI_Address() {
	D_OutInfo();
	auto spC_Address = C_Address::NewC_Address();
	auto spI_Address = spC_Address->GetSPI_Address();
	return spI_Address;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif