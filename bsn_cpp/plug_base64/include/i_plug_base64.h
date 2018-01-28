#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_base64)
//////////////////////////////////////////////////////////////////////
class I_PlugBase64 : public D_N1(plug_mgr)::I_Plug {
public:
	typedef std::shared_ptr<I_PlugBase64> T_SPI_PlugBase64;
	
public:
	virtual bool Encode(std::string const& strInput, std::string& strOut)  = 0;  
	virtual bool Decode(std::string const& strInput, std::string& strOut)  = 0; 

public:
	T_SPI_PlugBase64 GetSPI_PlugBase64() {
		D_OutInfo();
		auto spI_Plug = GetSPI_Plug();
		auto spI_PlugBase64 = std::dynamic_pointer_cast<I_PlugBase64>(spI_Plug);
		return spI_PlugBase64;
	}

public:
	virtual ~I_PlugBase64() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End