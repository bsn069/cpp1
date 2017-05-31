#include "./main.h"
#include "./service.h"

using namespace N_Bsn;
using D_N1(Global)::I_Service;
using namespace D_N1(ServiceTCPClient);
//////////////////////////////////////////////////////////////////////
D_BSN_service_tcp_client_DLL D_N1(Global)::I_Service* Create()
{
	C_Service* pImp = New<C_Service>();
	return pImp;
}


D_BSN_service_tcp_client_DLL T_void Release(D_N1(Global)::I_Service* pService)
{
	C_Service* pImp = static_cast<C_Service*>(pService);
	Delete(pImp);
}

