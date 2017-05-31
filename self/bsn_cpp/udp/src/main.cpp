#include "./main.h"



D_BsnNamespace1(UDP)
//////////////////////////////////////////////////////////////////////
D_FunImp D_BSN_udp_DLL T_void Release(I_Interface* pInterface)
{
	delete pInterface;
}

D_BsnNamespace1End
