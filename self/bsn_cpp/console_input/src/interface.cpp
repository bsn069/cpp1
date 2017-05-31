#include "./interface.h"
D_BsnNamespace1(ConsoleInput)
//////////////////////////////////////////////////////////////////////

T_wchar D_const * D_const C_Interface::Error(T_int32 D_const i32ErrorCode) D_const
{
	switch (i32ErrorCode)
	{
		case 1: return L"1";
		default: return L"Unknown";
	}
}


T_wchar D_const * D_const  C_Interface::Name() D_const
{
	return L"C_Imp";
}


C_Interface::C_Interface()
	: m_bQuit(false)
	, m_pThread(nullptr)
{

}


C_Interface::~C_Interface()
{
	if (nullptr != m_pThread)
	{
		if (!m_bQuit)
		{
			m_bQuit = true;
		}
		m_pThread->join();
		Delete(m_pThread);
	}
}


T_void
C_Interface::Thread()
{
	wstring wstrCmd;
	T_wchar wcInput;

	while (!m_bQuit)
	{
		wstrCmd.clear();
		while ((wcInput = getwchar()) != L'\n')
		{
			wstrCmd += wcInput;
		}
		if (wstrCmd.compare(L"quit") == 0)
		{
			m_bQuit = true;
			break;
		}
		m_Output.WriteRef(wstrCmd);
	}
}


T_int32 D_const
C_Interface::Start()
{
	if (nullptr != m_pThread)
	{
		return -1;
	}
	m_pThread = New<thread>(bind(&C_Interface::Thread, this));

	return 0;
}


I_Interface::T_Cmds*
C_Interface::GetCmds()
{
	return &(m_Output.Flip());
}


T_bool D_const
C_Interface::IsQuit() D_const
{
	return m_bQuit;
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
