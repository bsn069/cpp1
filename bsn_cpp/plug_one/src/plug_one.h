#pragma once

#include "./../include/i_plug_one.h"
 
D_BsnNamespace1(plug_one)
//////////////////////////////////////////////////////////////////////
class C_PlugOne : public I_PlugOne {
public:
	typedef std::shared_ptr<C_PlugOne> T_SPC_PlugOne;	

public:
	virtual void Awake() override;
	virtual void Init(T_SPI_PlugMgr spI_PlugMgr) override;
	virtual void Update() override;
	virtual void UnInit() override;

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