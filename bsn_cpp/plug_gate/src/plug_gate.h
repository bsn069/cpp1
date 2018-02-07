#pragma once

#include <bsn_cpp/plug_gate/include/i_plug_gate.h>
#include <bsn_cpp/plug_net/include/i_tcp_listen.h>
#include <bsn_cpp/plug_net/include/i_tcp_session.h>

#include <boost/function.hpp>

#include <map>

D_BsnNamespace1(plug_gate)
//////////////////////////////////////////////////////////////////////
class C_PlugGate : public I_PlugGate {
public:
	typedef std::shared_ptr<C_PlugGate> T_SPC_PlugGate;	
	typedef D_N1(plug_net)::I_TCPListen::T_SPI_TCPListen T_SPI_TCPListen;
	typedef D_N1(plug_net)::I_TCPSession::T_SPI_TCPSession T_SPI_TCPSession;
	typedef std::set<T_SPI_TCPSession> T_Sessions;

public: // I_Plug
	virtual char const * const GetName() const override;

	virtual bool OnLoad(std::set<std::string>& needPlugNames) override;
	virtual bool Init(T_SPI_PlugMgr spI_PlugMgr) override;
	virtual bool AllInitAfter() override;
	virtual bool Update() override;
	virtual bool Quit() override;
	virtual bool UnInit() override;

	virtual void ProcCmd(std::string const& strNet) override {};

	virtual void OnReloadPre(std::string const& strName) override;
	virtual void OnReloadPost(std::string const& strName) override;

public: // I_PlugGate

public:
	static T_SPC_PlugGate NewC_PlugGate(void* pData);
	static T_SPI_PlugGate NewI_PlugGate(void* pData);

	T_SPC_PlugGate GetSPC_PlugGate();
	bool RegAllCmd();
	bool StartClientListen();

	T_SPI_TCPSession FuncNew();
	void FuncOnAccept(T_SPI_TCPSession spI_TCPSession);

public:  
	void CmdHelp(bool bShowHelp, std::string const& strParam);

public:
	C_PlugGate(void* pData);
	virtual ~C_PlugGate();

public:
	T_SPI_PlugMgr 	m_spI_PlugMgr;
	T_SPI_TCPListen m_spI_TCPListen;
	T_Sessions		m_clientSessions;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End