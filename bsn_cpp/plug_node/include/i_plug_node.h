#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <stdint.h>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
class I_PlugNode : public D_N1(plug_mgr)::I_Plug {
public:
	typedef std::shared_ptr<I_PlugNode> T_SPI_PlugNode;

public:
	virtual void StartPlug(std::string const& strPlug) {};
 
public:
	T_SPI_PlugNode GetSPI_PlugNode() {
		D_OutInfo();
		auto spI_Plug = GetSPI_Plug();
		auto spI_PlugNode = std::dynamic_pointer_cast<I_PlugNode>(spI_Plug);
		return spI_PlugNode;
	}

public:
	virtual ~I_PlugNode() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End