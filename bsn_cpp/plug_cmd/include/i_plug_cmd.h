#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/name_space.h>

#include <boost/function.hpp>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_cmd)
//////////////////////////////////////////////////////////////////////
class I_PlugCmd : public D_N1(plug_mgr)::I_Plug {
public:
	typedef std::shared_ptr<I_PlugCmd> T_SPI_PlugCmd;
	typedef boost::function<void(bool, std::string const&)> T_FuncCmd;

public:
	virtual void RegPlug(std::string const& strName) = 0;
	virtual bool HadRegPlug(std::string const& strName) = 0;

	virtual std::string const& GetCurPlug() = 0;

	virtual void CDPlug(std::string const& strName) = 0;
	virtual void QuitPlug(std::string const& strName) = 0;
	
	virtual void RegPlugCmd(
					std::string const& strPlug
					, std::string const& strCmd
					, T_FuncCmd funcCmd
				) = 0;

public:
	T_SPI_PlugCmd GetSPI_PlugCmd() {
		D_OutInfo();
		auto spI_Plug = GetSPI_Plug();
		auto spI_PlugCmd = std::dynamic_pointer_cast<I_PlugCmd>(spI_Plug);
		return spI_PlugCmd;
	}

public:
	virtual ~I_PlugCmd() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End