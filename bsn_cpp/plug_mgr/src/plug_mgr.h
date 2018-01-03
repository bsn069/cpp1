#pragma once

#include "./../include/i_plug_mgr.h"
#include "./../include/i_plug.h"
 
#include "plug_data.h"

#include <boost/asio.hpp>

#include <map>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class C_PlugMgr : public I_PlugMgr {
public:
	typedef std::shared_ptr<C_PlugMgr> T_SPC_PlugMgr;	
	typedef std::map<std::string, C_PlugData::T_SPC_PlugData> T_Name2PlugData;

public:
	virtual void Run() override;
	virtual I_Plug::T_SPI_Plug GetPlug(std::string strName) override;
	virtual bool ReloadPlug(std::string const& strName) override;

	virtual void PushCmd(std::string const& strCmd) override;
	virtual void Quit() override;
	virtual bool IsQuit() override;


public:
	static T_SPC_PlugMgr NewC_PlugMgr();
	static T_SPI_PlugMgr NewI_PlugMgr();

	T_SPC_PlugMgr GetSPC_PlugMgr();

	bool LoadAll();
	bool AwakeAll();
	bool InitAll();
	bool AllInitAfter();
	void Update(const boost::system::error_code& ec);
	void QuitAll();
	void UnInitAll();

	void WaitUpdate();
	void ProcCmd(std::string const& strCmd);

	C_PlugData::T_SPC_PlugData GetPlugData(std::string const& strName);
	C_PlugData::T_SPC_PlugData LoadPlugData(std::string const& strName);
	
	bool DoReloadPlug(std::string const& strName);
	
public:
	T_Name2PlugData m_Name2PlugData;

	uint32_t 					m_u32FrameMS;
	boost::asio::io_service 	m_ioService;
	boost::asio::deadline_timer	m_updateTimer;
	std::string 				m_waitReloadPlug;

public:
	C_PlugMgr();
	virtual ~C_PlugMgr();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End