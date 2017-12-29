#pragma once

#include "./../include/i_plug_one.h"
 
D_BsnNamespace1(plug_one)
//////////////////////////////////////////////////////////////////////
class C_PlugOne : public I_PlugOne {
public:
	typedef std::shared_ptr<C_PlugOne> T_SPC_PlugOne;	

public:
	virtual void Awake() override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void UnInit() override;

public:
	C_PlugOne();
	virtual ~C_PlugOne();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End