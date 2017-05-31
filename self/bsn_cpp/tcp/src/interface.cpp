#include "./main.h"
#include "./interface.h"
#include "./server.h"
#include "./client.h"
D_BsnNamespace1(TCP)
//////////////////////////////////////////////////////////////////////


D_FunImp D_BSN_tcp_DLL I_Interface* Create()
{
	return new C_Interface;
}

D_FunImp D_BSN_tcp_DLL T_int32 D_const Release(I_Interface*& pInterface)
{
	C_Interface* pImp = static_cast<C_Interface*>(pInterface);
	pImp->Stop();
	Delete(pImp);
	pInterface = T_nullptr;
	return 0;
}

T_wchar D_const * D_const  C_Interface::Name() D_const
{
	return L"C_Imp";
}


T_wchar D_const * D_const C_Interface::Error(T_int32 D_const i32ErrorCode) D_const
{
	switch ( i32ErrorCode )
	{
		case -999: return L"";
		case -1: return L"had start";
		case -2: return L"not start";
		case -3: return L"not start";
		case -4: return L"had bind";
		case -5: return L"not bind";
		case -6: return L"had listen";
		case -7: return L"not listen";
		case -8: return L"is close";
		case -9: return L"not connect";
		case 1: return L"had init";
		case 2: return L"not init";
		default: return L"Unknown";
	}
}


T_int32 D_const
C_Interface::CreateServer(I_Server*& pServer)
{
	if (!IsStart())
	{
		return -3;
	}

	pServer = New<C_Server>(*this, m_IOService);
	return 0;
}


T_int32 D_const
C_Interface::ReleaseServer(I_Server*& pServer)
{
	C_Server* pImp = static_cast<C_Server*>(pServer);
	pImp->StopListen();
	Delete(pImp);
	pServer = T_nullptr;
	return 0;

}


T_int32 D_const
C_Interface::CreateClient(I_Client*& pClient)
{
	pClient = New<C_Client>(*this);
	return 0;
}


T_int32 D_const
C_Interface::ReleaseClient(I_Client*& pClient)
{
	C_Client* pImp = static_cast<C_Client*>(pClient);
	Delete(pImp);
	pClient = T_nullptr;
	return 0;
}



C_Interface::C_Interface()
	: m_pWork( T_nullptr )
{
}


T_int32 D_const
C_Interface::Start()
{
	if (IsStart())
	{
		return -1;
	}

	m_pWork = New<asio::io_service::work>(m_IOService);
	for (T_uint32 i = 0; i < 2; ++i)
	{
		m_ThreadGroup.create_thread(bind(&asio::io_service::run, &m_IOService));
	}
	return 0;
}


T_int32 D_const
C_Interface::Stop()
{
	if (!IsStart())
	{
		return -2;
	}

	m_IOService.stop();
	Delete(m_pWork);
	m_ThreadGroup.join_all();
	return 0;
}







D_BsnNamespace1End
