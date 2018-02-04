#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_client)
//////////////////////////////////////////////////////////////////////
class I_PlugClient : public D_N1(plug_mgr)::I_Plug {
public:
	typedef std::shared_ptr<I_PlugClient> T_SPI_PlugClient;
	
public:

public:
	T_SPI_PlugClient GetSPI_PlugClient() {
		D_OutInfo();
		auto spI_Plug = GetSPI_Plug();
		auto spI_PlugClient = std::dynamic_pointer_cast<I_PlugClient>(spI_Plug);
		return spI_PlugClient;
	}

public:
	virtual ~I_PlugClient() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End