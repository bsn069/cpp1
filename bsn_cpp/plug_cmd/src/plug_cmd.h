#pragma once

#include <bsn_cpp/plug_cmd/include/i_plug_cmd.h>
#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_cmd.h>

#include <map>

D_BsnNamespace1(plug_cmd)
//////////////////////////////////////////////////////////////////////
class C_PlugCmd : public I_PlugCmd {
public:
	typedef std::shared_ptr<C_PlugCmd> T_SPC_PlugCmd;	
	typedef D_N1(plug_mgr)::C_PlugDataCmd T_PlugData;
	typedef std::map<std::string, T_FuncCmd> T_Cmd2Func;
	typedef std::map<std::string, T_Cmd2Func> T_PlugCmds;

public: // I_Plug
	virtual char const * const GetName() const override;

	virtual bool OnLoad(std::set<std::string>& needPlugNames) override;
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
	
	virtual void RegPlugCmd(
					std::string const& strPlug
					, std::string const& strCmd
					, T_FuncCmd funcCmd
				) override;
public:
	static T_SPC_PlugCmd NewC_PlugCmd(void* pData);
	static T_SPI_PlugCmd NewI_PlugCmd(void* pData);

	T_SPC_PlugCmd GetSPC_PlugCmd();

	bool DoCmd(
			std::string const& strPlug
			, std::string const& strCmd
			, std::string const& strParam
		);

public: // cmd
	void CmdQuit(bool bShowHelp, std::string const& strParam);
	void CmdLS(bool bShowHelp, std::string const& strParam);
	void CmdCD(bool bShowHelp, std::string const& strParam);
	void CmdPWD(bool bShowHelp, std::string const& strParam);
	void CmdPushD(bool bShowHelp, std::string const& strParam);
	void CmdPopD(bool bShowHelp, std::string const& strParam);
	void CmdReloadPlug(bool bShowHelp, std::string const& strParam);
	void CmdHelp(bool bShowHelp, std::string const& strParam);

public:
	C_PlugCmd(void* pData);
	virtual ~C_PlugCmd();

public:
	T_SPI_PlugMgr 	m_spI_PlugMgr;
	T_PlugData* 	m_pData;
	T_PlugCmds		m_PlugCmds;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End