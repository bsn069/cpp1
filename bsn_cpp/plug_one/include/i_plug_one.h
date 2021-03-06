#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_one)
//////////////////////////////////////////////////////////////////////
class I_PlugOne : public D_N1(plug_mgr)::I_Plug {
public:
	typedef std::shared_ptr<I_PlugOne> T_SPI_PlugOne;
	
public:
	T_SPI_PlugOne GetSPI_PlugOne() {
		D_OutInfo();
		auto spI_Plug = GetSPI_Plug();
		auto spI_PlugOne = std::dynamic_pointer_cast<I_PlugOne>(spI_Plug);
		return spI_PlugOne;
	}

public:
	virtual ~I_PlugOne() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End