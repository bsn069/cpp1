#pragma once

#include <bsn_cpp/plug_net/include/i_plug_net.h>
#include <bsn_cpp/plug_mgr/include/plug_data/plug_data_net.h>
#include <bsn_cpp/plug_net/include/i_dns.h>

#include <boost/function.hpp>

#include <map>

D_BsnNamespace1(plug_net)
//////////////////////////////////////////////////////////////////////
class C_PlugNet : public I_PlugNet {
public:
	typedef std::shared_ptr<C_PlugNet> T_SPC_PlugNet;	
	typedef D_N1(plug_mgr)::C_PlugDataNet T_PlugData;

public: // I_Plug
	virtual char const * const GetName() const override;

	virtual bool Awake() override;
	virtual bool Init(T_SPI_PlugMgr spI_PlugMgr) override;
	virtual bool AllInitAfter() override;
	virtual bool Update() override;
	virtual bool Quit() override;
	virtual bool UnInit() override;

	virtual void ProcCmd(std::string const& strNet) {};

	virtual void OnReloadPre(std::string const& strName) override;
	virtual void OnReloadPost(std::string const& strName) override;

public: // I_PlugNet
 	virtual I_Dns::T_SPI_Dns 	NewI_Dns() override;
 	virtual T_SPI_TCPListen 	NewI_TCPListen() override;
	virtual T_SPI_TCPConnect 	NewI_TCPConnect() override;
 	virtual T_SPI_Address 		NewI_Address() override;


public:
	static T_SPC_PlugNet NewC_PlugNet(void* pData);
	static T_SPI_PlugNet NewI_PlugNet(void* pData);

	T_SPC_PlugNet GetSPC_PlugNet();
	bool RegAllCmd();
	boost::asio::io_service& GetIOService();


public:  
	void CmdHelp(bool bShowHelp, std::string const& strParam);
	void CmdShowIP(bool bShowHelp, std::string const& strParam);
	void CmdShowIPAsync(bool bShowHelp, std::string const& strParam);
	void CmdHttpGet(bool bShowHelp, std::string const& strParam);
	void CmdHttpGetCoro(bool bShowHelp, std::string const& strParam);
	void CmdHttpsGet(bool bShowHelp, std::string const& strParam);
	void CmdHttpGetAsync(bool bShowHelp, std::string const& strParam);
	void CmdURL(bool bShowHelp, std::string const& strParam);
	void CmdHttpServer(bool bShowHelp, std::string const& strParam);
	void CmdSendMail(bool bShowHelp, std::string const& strParam);

public:
	C_PlugNet(void* pData);
	virtual ~C_PlugNet();

public:
	// T_SPI_PlugMgr 	m_spI_PlugMgr;
	T_PlugData* 	m_pData;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End