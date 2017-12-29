#pragma once

#include "./../include/i_plug_mgr.h"
 
#include <map>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class C_PlugMgr : public I_PlugMgr {
public:
	typedef std::shared_ptr<C_PlugMgr> T_SPC_PlugMgr;	

public:
	virtual void Run() override;
	virtual I_Plug::T_SPI_Plug GetPlug(std::string strName) override;

public:
	T_SPC_PlugMgr GetSPC_PlugMgr();

	static T_SPC_PlugMgr NewC_PlugMgr();
	static T_SPI_PlugMgr NewI_PlugMgr();

public:
	std::map<std::string, I_Plug::T_SPI_Plug> m_Name2Plug;

public:
	C_PlugMgr();
	virtual ~C_PlugMgr();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End