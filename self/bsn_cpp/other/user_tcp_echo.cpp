#include "./user_tcp_echo.h"
#include "./user_tcp.cpp"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////




C_UserTCPEcho::C_UserTCPEcho()
{
}



C_UserTCPEcho::~C_UserTCPEcho()
{
}


T_int32 D_const
C_UserTCPEcho::ProcMsg()
{
	D_Assert(nullptr != m_pMsgs);

	for (auto i : *m_pMsgs)
	{

	}

	return 0;
}



D_BsnNamespace1End
