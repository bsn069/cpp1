#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>
#include <string>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class I_PlugMgr;

class I_Plug : public std::enable_shared_from_this<I_Plug> {
public:
	typedef std::shared_ptr<I_Plug> T_SPI_Plug;
	typedef std::shared_ptr<I_PlugMgr> T_SPI_PlugMgr;

public:
	virtual char const * const GetName() const = 0;

	virtual bool Awake() = 0;
	virtual bool Init(T_SPI_PlugMgr spI_PlugMgr) = 0;
	virtual bool AllInitAfter() = 0;
	virtual bool Update() = 0;
	virtual bool Quit() = 0;
	virtual bool UnInit() = 0;

	virtual void OnReloadPre(std::string const& strName) = 0;
	virtual void OnReloadPost(std::string const& strName) = 0;

	virtual void ProcCmd(std::string const& strCmd) = 0;

	T_SPI_Plug GetSPI_Plug() {
		return shared_from_this();
	}

public:
	virtual ~I_Plug() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
