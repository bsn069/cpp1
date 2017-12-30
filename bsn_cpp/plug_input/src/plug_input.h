#pragma once

#include "./../include/i_plug_input.h"
 
D_BsnNamespace1(plug_input)
//////////////////////////////////////////////////////////////////////
class C_PlugInput : public I_PlugInput {
public:
	typedef std::shared_ptr<C_PlugInput> T_SPC_PlugInput;	

public:
	virtual void Awake() override;
	virtual void Init(T_SPI_PlugMgr spI_PlugMgr) override;
	virtual void Update() override;
	virtual void UnInit() override;

public:
	static T_SPC_PlugInput NewC_PlugInput();
	static T_SPI_PlugInput NewI_PlugInput();

	T_SPC_PlugInput GetSPC_PlugInput();

public:
	C_PlugInput();
	virtual ~C_PlugInput();

public:
	T_SPI_PlugMgr m_spI_PlugMgr;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End