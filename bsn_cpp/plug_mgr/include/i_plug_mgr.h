#pragma once

#include <bsn_cpp/plug_mgr/include/i_plug.h>

#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/d_out.h>

#include <boost/asio.hpp>
#include <bsn_cpp/third_part/LuaJIT/src/lua.hpp>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class I_PlugMgr : public std::enable_shared_from_this<I_PlugMgr> {
public:
	typedef std::shared_ptr<I_PlugMgr> T_SPI_PlugMgr;
	typedef boost::asio::io_service T_IOService;

public:
	virtual void Run(char const * pszConfigFile) = 0;
	
	virtual I_Plug::T_SPI_Plug GetPlug(std::string strName) = 0;
	virtual bool ReloadPlug(std::string const& strName) = 0;

	virtual void PushCmd(std::string const& strCmd) = 0;
	virtual void Quit() = 0;
	virtual bool IsQuit() = 0;

	virtual T_IOService& GetIOService() = 0;
	virtual lua_State* GetLuaState() const = 0;

public:
	T_SPI_PlugMgr GetSPI_PlugMgr() {
		return shared_from_this();
	}

	template<typename T>
	std::shared_ptr<T> GetPlugPtr(std::string const& strPlugName) {
		D_OutInfo1(strPlugName);

		auto spI_Plug = GetPlug(strPlugName);
		if (!spI_Plug) {
			return nullptr;
		}

		return std::dynamic_pointer_cast<T>(spI_Plug);
	}

public:
	virtual ~I_PlugMgr() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End