#pragma once

#include "./../include/i_plug_mgr.h"
#include "./../include/i_plug.h"
 
#include "plug_data.h"

#include <map>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class C_PlugMgr : public I_PlugMgr {
public:
	typedef std::shared_ptr<C_PlugMgr> T_SPC_PlugMgr;	
	typedef std::map<std::string, C_PlugData> T_Name2PlugData;

public:
	virtual void Run() override;
	virtual I_Plug::T_SPI_Plug GetPlug(std::string strName) override;
	virtual T_SPI_PlugMgr GetSPI_PlugMgr() override;

public:
	static T_SPC_PlugMgr NewC_PlugMgr();
	static T_SPI_PlugMgr NewI_PlugMgr();

	T_SPC_PlugMgr GetSPC_PlugMgr();

	void Awake();
	void Init();
	void Update();
	void UnInit();

public:
	T_Name2PlugData m_Name2PlugData;

public:
	C_PlugMgr();
	virtual ~C_PlugMgr();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End