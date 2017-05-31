#pragma once
#include "./user_tcp.h"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////

class C_UserTCPEcho : public C_UserTCP
{
public:
	typedef C_UserTCP T_Base;


public:


public:
	C_UserTCPEcho();
	~C_UserTCPEcho();


protected:


protected:
	virtual T_int32 D_const	ProcMsg() override;

};

 

D_BsnNamespace1End
