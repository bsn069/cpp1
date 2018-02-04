#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_gate)
//////////////////////////////////////////////////////////////////////
class I_PlugGate : public D_N1(plug_mgr)::I_Plug {
public:
	typedef std::shared_ptr<I_PlugGate> T_SPI_PlugGate;
	
public:

public:
	T_SPI_PlugGate GetSPI_PlugGate() {
		D_OutInfo();
		auto spI_Plug = GetSPI_Plug();
		auto spI_PlugGate = std::dynamic_pointer_cast<I_PlugGate>(spI_Plug);
		return spI_PlugGate;
	}

public:
	virtual ~I_PlugGate() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End