#pragma once

#include "./../include/i_plug_mgr.h"
 
D_BsnNamespace1(plug_mgr)
//////////////////////////////////////////////////////////////////////
class C_PlugMgr : public I_PlugMgr {
public:
	typedef std::shared_ptr<C_PlugMgr> T_SPC_PlugMgr;	

public:
	C_PlugMgr();
	virtual ~C_PlugMgr();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End