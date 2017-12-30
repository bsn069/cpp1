#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_input)
//////////////////////////////////////////////////////////////////////
class I_PlugInput : public D_N1(plug_mgr)::I_Plug {
public:
	typedef std::shared_ptr<I_PlugInput> T_SPI_PlugInput;
	
public:
	T_SPI_PlugInput GetSPI_PlugInput() {
		D_OutInfo();
		auto spI_Plug = GetSPI_Plug();
		auto spI_PlugInput = std::dynamic_pointer_cast<I_PlugInput>(spI_Plug);
		return spI_PlugInput;
	}

public:
	virtual ~I_PlugInput() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End