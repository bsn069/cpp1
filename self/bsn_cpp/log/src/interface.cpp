#include "./interface.h"
D_BsnNamespace1(Log)
//////////////////////////////////////////////////////////////////////

C_Interface::C_Interface()
	: m_bQuit( false )
	, m_LevelOutput(integer_traits<T_Level>::const_max)
	, m_LevelLog(integer_traits<T_Level>::const_max)
	, m_pThread( nullptr )
{
	m_CallBackOutput = bind(&C_Interface::CallBackOutput, this, _1, _2);
	m_CallBackLog = bind(&C_Interface::CallBackLog, this, _1, _2);
}

C_Interface::~C_Interface()
{
	if (nullptr != m_pThread)
	{
		m_bQuit = true;
		m_pThread->join();
		Delete(m_pThread);
		Process();
	}
}


T_wchar D_const * D_const  C_Interface::Name() D_const
{
	return L"C_Imp";
}


T_wchar D_const * D_const C_Interface::Error(T_int32 D_const i32ErrorCode) D_const
{
	switch ( i32ErrorCode )
	{
	case -1: return L"had start";
	default: return L"Unknown";
	}
}


N_Bsn::T_void
C_Interface::Thread()
{
	auto sleepMs = milliseconds(100);
	while (!m_bQuit)
	{
		Process();
		sleep_for(sleepMs);
	}
}


T_int32 D_const
C_Interface::Write(T_Level D_const level, T_wchar D_const * D_const pwcLog)
{
	m_Output.Write(pwcLog);
	return 0;
}


T_int32 D_const
C_Interface::Write(T_wchar D_const * D_const pwcModule, T_Level D_const Level, T_wchar D_const * D_const pwcLog, T_wchar D_const * D_const pwcFile, T_wchar D_const * D_const pwcFunction, T_uint32 D_const u32Line)
{
	wstring wstrLog = str(wformat(L"%1% \t%2%:%3%")
		% pwcLog
		% pwcFile
		% u32Line
		);
	return Write(Level, wstrLog.c_str());
}


T_int32 D_const
C_Interface::SetLevelOutput(T_Level D_const Level)
{
	m_LevelOutput = Level;
	return 0;
}


T_int32 D_const
C_Interface::GetLevelOutput(T_Level& Level) D_const
{
	Level = m_LevelOutput;
	return 0;
}


T_int32 D_const
C_Interface::SetLevelLog(T_Level D_const Level)
{
	m_LevelLog = Level;
	return 0;
}


T_int32 D_const
C_Interface::GetLevelLog(T_Level& Level) D_const
{
	Level = m_LevelLog;
	return 0;
}


N_Bsn::T_void
C_Interface::CallBackOutput(T_Level D_const Level, wstring D_const& wstrLog)
{
	wcout << wstrLog << endl;
}


N_Bsn::T_void
C_Interface::CallBackLog(T_Level D_const Level, wstring D_const& wstrLog)
{

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


T_int32 D_const
C_Interface::SetCallBackOutput(T_CallBack CallBack)
{
	if (nullptr != m_pThread)
	{
		return -1;
	}

	m_CallBackOutput = CallBack;
	return 0;
}


T_int32 D_const
C_Interface::SetCallBackLog(T_CallBack CallBack)
{
	if (nullptr != m_pThread)
	{
		return -1;
	}

	m_CallBackLog = CallBack;
	return 0;
}


void
C_Interface::Process()
{
	T_Level Level = integer_traits<T_Level>::const_max;
	T_Logs& log = m_Output.Flip();
	for (auto D_const& strLog : log)
	{
		if (0 != (m_LevelOutput & Level))
		{
			m_CallBackOutput(Level, strLog);
		}
		if (0 != (m_LevelLog & Level))
		{
			m_CallBackLog(Level, strLog);
		}
	}
}






//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
