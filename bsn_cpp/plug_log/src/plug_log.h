#pragma once

#include "./../include/i_plug_log.h"
// #include <bsn_cpp/plug_mgr/include/plug_data_log.h>

D_BsnNamespace1(plug_log)
//////////////////////////////////////////////////////////////////////
class C_PlugLog : public I_PlugLog {
public:
	typedef std::shared_ptr<C_PlugLog> T_SPC_PlugLog;	
	typedef void T_PlugData;

public: // I_Plug
	virtual bool Awake() override;
	virtual bool Init(T_SPI_PlugMgr spI_PlugMgr) override;
	virtual bool AllInitAfter() override;
	virtual bool Update() override;
	virtual bool Quit() override;
	virtual bool UnInit() override;

	virtual void ProcCmd(std::string const& strCmd) override;

	virtual void OnReloadPre(std::string const& strName) override;
	virtual void OnReloadPost(std::string const& strName) override;

public: // I_PlugLog
 
	

public:
	static T_SPC_PlugLog NewC_PlugLog();
	static T_SPI_PlugLog NewI_PlugLog();

	T_SPC_PlugLog GetSPC_PlugLog();

public:
	C_PlugLog();
	virtual ~C_PlugLog();

public:
	T_SPI_PlugMgr 	m_spI_PlugMgr;
	// T_PlugData* 	m_pData;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End