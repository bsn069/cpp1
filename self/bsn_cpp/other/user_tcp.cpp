#include <bsn/msg_parser/include/port.h>
#include "./user_tcp.h"
#include "./user.cpp"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////




C_UserTCP::C_UserTCP()
{
}



C_UserTCP::~C_UserTCP()
{
}





T_int32 D_const
C_UserTCP::SetSession(T_SessionPtr& Session)
{
	D_AssertRet(Session, 1);
	D_AssertRet(!m_Session, 1);

	m_Session = Session;
	return 0;
}


T_int32 D_const
C_UserTCP::RecvMsg()
{
	if (!m_Session)
	{
		return 1;
	}
	if (T_nullptr == m_pMsgParser)
	{
		return 5;
	}

	T_Buffers* pBuffers = T_nullptr;
	T_int32 i32Ret = m_Session->Recv(pBuffers);
	if (0 != i32Ret)
	{
		return 10;
	}
	if (pBuffers->empty())
	{
		return 0;
	}

	i32Ret = m_pMsgParser->Push(pBuffers);
	if (0 != i32Ret)
	{
		return 6;
	}

	return 0;
}




D_BsnNamespace1End
