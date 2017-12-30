#pragma once

#include "./../include/i_plug_mgr.h"
#include "./../include/i_plug.h"
 
#include "plug_data.h"
#include <bsn_cpp/include/double_list.hpp>

#include <boost/asio.hpp>

#include <map>

D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class C_PlugMgr : public I_PlugMgr {
public:
	typedef std::shared_ptr<C_PlugMgr> T_SPC_PlugMgr;	
	typedef std::map<std::string, C_PlugData::T_SPC_PlugData> T_Name2PlugData;
	typedef std::vector<std::string> T_Cmds;

public:
	virtual void Run() override;
	virtual I_Plug::T_SPI_Plug GetPlug(std::string strName) override;
	virtual void PushCmd(std::string const& strCmd) override;
	virtual void Quit() override;

public:
	static T_SPC_PlugMgr NewC_PlugMgr();
	static T_SPI_PlugMgr NewI_PlugMgr();

	T_SPC_PlugMgr GetSPC_PlugMgr();

	void Awake();
	void Init();
	void Update(const boost::system::error_code& ec);
	void UnInit();

	void WaitUpdate();
	void ProcCmd(std::string const& strCmd);


public:
	T_Name2PlugData m_Name2PlugData;

	uint32_t 					m_u32FrameMS;
	boost::asio::io_service 	m_ioService;
	boost::asio::deadline_timer	m_updateTimer;
	bool 						m_bQuit;
	C_DoubleList<T_Cmds> 		m_InputCmd;

public:
	C_PlugMgr();
	virtual ~C_PlugMgr();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End