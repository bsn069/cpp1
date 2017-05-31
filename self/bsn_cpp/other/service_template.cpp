#include "./service_template.h"
#include "./service_mgr_user_tcp.cpp"
using D_N1(ServiceTemplate)::C_Service;
#include "./main_service.cpp"
D_BsnNamespace1(ServiceTemplate)
//////////////////////////////////////////////////////////////////////

#define  D_MyLog(wstrOut) \
D_Log(m_pGlobal->Log(), wstrOut.c_str())

T_wchar D_const * D_const  C_Service::Name() D_const
{
	// ÎÄ¼þ¼ÐÃû
	return L"service_template";
}


T_wchar D_const * D_const C_Service::Error(T_int32 D_const i32ErrorCode) D_const
{
	if (i32ErrorCode < 0)
	{
		return I_Service::Error(i32ErrorCode);
	}

	switch (i32ErrorCode)
	{
		case 1: return L"???";
		default: return L"Unknown";
	}
}



C_Service::C_Service()
{
}



C_Service::~C_Service()
{

}


T_int32 D_const
C_Service::Init(T_Global* pGlobal)
{
	T_Base::Init(pGlobal);

	RegCmd(L"Test", bind(&C_Service::Cmd_Test, this, _1));

	return 0;
}


T_int32 D_const
C_Service::Uninit()
{
	T_Base::Uninit(); 
	return 0;
}


T_int32 D_const
C_Service::Update()
{
	return 0;
}


N_Bsn::T_void
C_Service::Cmd_Test(T_Cmds D_const& Cmds)
{
	wstring wstrOut;
	for (size_t i = 0; i < Cmds.size(); ++i)
	{
		wstrOut = str(wformat(L"Cmds[%1%]= %2%")
			% i
			% Cmds[i]
			);
		D_MyLog(wstrOut);
	}

	wstrOut = L"success";
	D_MyLog(wstrOut);
}

D_BsnNamespace1End
