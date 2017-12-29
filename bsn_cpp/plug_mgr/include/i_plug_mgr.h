#pragma once

#include <bsn_cpp/include/name_space.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class I_PlugMgr : public std::enable_shared_from_this<I_PlugMgr> {
public:
	typedef std::shared_ptr<I_PlugMgr> T_SPI_PlugMgr;
	
public:
	virtual void Awake() = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void UnInit() = 0;
	
	virtual void Run() = 0;
	virtual I_Plug::T_SPI_Plug GetPlug(std::string strName) = 0;
	
public:
	T_SPI_PlugMgr GetSPI_PlugMgr() {
		return share_from_this();
	};

public:
	virtual ~I_PlugMgr() = default;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End