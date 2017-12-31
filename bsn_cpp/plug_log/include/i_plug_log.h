#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_log)
//////////////////////////////////////////////////////////////////////
class I_PlugLog : public D_N1(plug_mgr)::I_Plug {
public:
	typedef std::shared_ptr<I_PlugLog> T_SPI_PlugLog;
	
public:
	

public:
	T_SPI_PlugLog GetSPI_PlugLog() {
		D_OutInfo();
		auto spI_Plug = GetSPI_Plug();
		auto spI_PlugLog = std::dynamic_pointer_cast<I_PlugLog>(spI_Plug);
		return spI_PlugLog;
	}

public:
	virtual ~I_PlugLog() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End