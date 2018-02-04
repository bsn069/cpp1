#pragma once

#include <bsn_cpp/plug_gate/include/i_plug_gate.h>

#include <boost/function.hpp>

#include <map>

D_BsnNamespace1(plug_gate)
//////////////////////////////////////////////////////////////////////
class C_PlugGate : public I_PlugGate {
public:
	typedef std::shared_ptr<C_PlugGate> T_SPC_PlugGate;	

public: // I_Plug
	virtual char const * const GetName() const override;

	virtual bool Awake() override;
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

public:  
	void CmdHelp(bool bShowHelp, std::string const& strParam);
	
public:
	C_PlugGate(void* pData);
	virtual ~C_PlugGate();

public:
	T_SPI_PlugMgr 	m_spI_PlugMgr;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End