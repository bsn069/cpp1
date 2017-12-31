#pragma once

#include "./../include/i_plug_one.h"
 
D_BsnNamespace1(plug_one)
//////////////////////////////////////////////////////////////////////
class C_PlugOne : public I_PlugOne {
public:
	typedef std::shared_ptr<C_PlugOne> T_SPC_PlugOne;	

public:
	virtual bool Awake() override;
	virtual bool Init(T_SPI_PlugMgr spI_PlugMgr) override;
	virtual bool AllInitAfter() override;
	virtual bool Update() override;
	virtual bool Quit() override;
	virtual bool UnInit() override;

	virtual void OnReloadPre(std::string const& strName) override;
	virtual void OnReloadPost(std::string const& strName) override;

	virtual void ProcCmd(std::string const& strCmd) override;

public:
	static T_SPC_PlugOne NewC_PlugOne();
	static T_SPI_PlugOne NewI_PlugOne();

	T_SPC_PlugOne GetSPC_PlugOne();

public:
	C_PlugOne();
	virtual ~C_PlugOne();

public:
	T_SPI_PlugMgr m_spI_PlugMgr;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End