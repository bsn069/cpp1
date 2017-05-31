#pragma once
#include <bsn/tcp/include/i_interface.h>
#include "./user.h"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////

class C_UserTCP : public C_User
{
public:
	typedef D_N1(TCP)::I_Session::T_Ptr		T_SessionPtr;
	typedef D_N1(TCP)::I_Session::T_Buffers T_Buffers;


public:
	T_int32 D_const	SetSession(T_SessionPtr& Session);


public:
	C_UserTCP();
	~C_UserTCP();


protected:
	T_SessionPtr	m_Session;


protected:
	virtual T_int32 D_const	RecvMsg() override;
};

 

D_BsnNamespace1End
