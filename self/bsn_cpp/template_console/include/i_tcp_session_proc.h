#pragma once

#include <bsn/include/port.h>
#include <bsn/tcp/include/port.h>

D_BsnNamespace1(Bin)
//////////////////////////////////////////////////////////////////////

class I_TcpSessionProc
{
public:
	typedef D_N1(TCP)::I_Session::T_Ptr T_SessionPtr;


public:
	virtual T_int32 D_const OnTcpSessionAccept(T_SessionPtr& sessionPtr) D_const = 0;
	virtual T_int32 D_const OnTcpSessionConnect(T_SessionPtr& sessionPtr) D_const = 0;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


