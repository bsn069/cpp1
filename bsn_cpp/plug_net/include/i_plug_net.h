#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class I_PlugNet : public D_N1(plug_mgr)::I_Plug {
public:
	typedef std::shared_ptr<I_PlugNet> T_SPI_PlugNet;
	
public:
 

public:
	T_SPI_PlugNet GetSPI_PlugNet() {
		D_OutInfo();
		auto spI_Plug = GetSPI_Plug();
		auto spI_PlugNet = std::dynamic_pointer_cast<I_PlugNet>(spI_Plug);
		return spI_PlugNet;
	}

public:
	virtual ~I_PlugNet() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End