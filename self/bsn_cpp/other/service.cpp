#pragma once
#include "./i_global.h"
#include "./service.h"
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////

T_wchar D_const * D_const 
I_Service::Error(T_int32 D_const i32ErrorCode) D_const
{
	switch (i32ErrorCode)
	{
		case -1: return L"InitÊ§°Ü£¬ÒÑInit";
		case -2: return L"UninitÊ§°Ü£¬ÒÑUninit";
		case -3: return L"UninitÊ§°Ü£¬Î´Init";
		default: return L"Unknown";
	}
}


I_Service::I_Service()
	: m_pGlobal( T_nullptr )
	, m_bInit(false)
	, m_bUninit(false)
{

}


I_Service::~I_Service()
{

}


T_int32 D_const
I_Service::Cmd(wstring D_const& wstrCmd, T_Cmds D_const& Cmds)
{
	auto itor = m_CmdFuncs.find(Cmds[0]);
	if (itor == m_CmdFuncs.end())
	{
		return 0;
	}
	auto& func = itor->second;
	func(Cmds);

	return 0;
}


T_bool D_const
I_Service::IsInit() D_const
{
	return m_bInit;
}


T_bool D_const
I_Service::IsUninit() D_const
{
	return m_bUninit;
}



T_int32 D_const
I_Service::Init(T_Global* pGlobal)
{
	if (IsInit())
	{
		return -1;
	}
	m_bInit = true;
	m_pGlobal = pGlobal;

	RegCmd(L"whoami", [&](T_Cmds D_const&){D_Log(m_pGlobal->Log(), Name());});

	return 0;
}


T_int32 D_const
I_Service::Uninit()
{
	if (IsUninit())
	{
		return -2;
	}
	if (!IsInit())
	{
		return -3;
	}
	m_bUninit = true;

	return 0;
}


N_Bsn::T_void
I_Service::RegCmd(wstring D_const& wstrCmd, T_CmdFunc cmdFunc)
{
	m_CmdFuncs.insert( make_pair(wstrCmd, cmdFunc) );
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


