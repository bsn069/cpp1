#pragma once

#include "./../include/i_plug_cmd.h"
#include <bsn_cpp/plug_mgr/include/plug_data_cmd.h>

D_BsnNamespace1(plug_cmd)
//////////////////////////////////////////////////////////////////////
class C_PlugCmd : public I_PlugCmd {
public:
	typedef std::shared_ptr<C_PlugCmd> T_SPC_PlugCmd;	
	typedef D_N1(plug_mgr)::C_PlugDataCmd T_PlugData;

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

public: // I_PlugCmd
	virtual void RegPlug(std::string const& strName) override;
	virtual bool HadRegPlug(std::string const& strName) override;

	virtual std::string const& GetCurPlug() override;

	virtual void CDPlug(std::string const& strName) override;
	virtual void QuitPlug(std::string const& strName) override;
	

public:
	static T_SPC_PlugCmd NewC_PlugCmd(void* pData);
	static T_SPI_PlugCmd NewI_PlugCmd(void* pData);

	T_SPC_PlugCmd GetSPC_PlugCmd();

public:
	C_PlugCmd(void* pData);
	virtual ~C_PlugCmd();

public:
	T_SPI_PlugMgr 	m_spI_PlugMgr;
	T_PlugData* 	m_pData;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End