#include "./interface.h"
#include <bsn/dynamic_lib/include/port.h>
#include <bsn/log/include/port.h>
#include <bsn/console_input/include/port.h>
#include <bsn/tcp/include/port.h>
#include <bsn/other/service.h>
#include <bsn/other/service.cpp>
D_BsnNamespace1(Global)
//////////////////////////////////////////////////////////////////////

T_wchar D_const * D_const C_Global::Error(T_int32 D_const i32ErrorCode) D_const
{
	switch (i32ErrorCode)
	{
		case 1: return L"1";
		default: return L"Unknown";
	}
}


T_wchar D_const * D_const  C_Global::Name() D_const
{
	return L"C_Imp";
}


C_Global::C_Global()
	: m_pLog( T_nullptr )
	, m_bQuit( false )
	, m_pTCP( T_nullptr )
{

}


C_Global::~C_Global()
{

}


T_int32 D_const 
C_Global::SetLog(T_Log* pLog)
{
	m_pLog = pLog;
	return 0;
}


I_Global::T_Log* 
C_Global::Log()
{
	return m_pLog;
}


N_Bsn::T_void
C_Global::Wmain(T_int32 argc, T_wchar* argv[])
{
	T_int32 i32Ret = 0;
	wstring wstrOut;

	if (!Init(argc, argv))
	{
		D_Log(m_pLog, L"Init fail");
		return;
	}

	wstring wstrSep(L" ");
	I_Service::T_Cmds Cmds;
	D_N1(ConsoleInput)::I_Interface::T_Cmds* pCmds = nullptr;
	while (!m_bQuit)
	{
		sleep_for(milliseconds(33));

		pCmds = m_pConsoleInput->GetCmds();
		for (auto& wstrCmd : *pCmds)
		{
			D_Log(m_pLog, wstrCmd.c_str());
			Cmds.clear();
			D_N1(String)::Split(wstrCmd, wstrSep, Cmds);
			if (Cmds.empty())
			{
				continue;
			}
			for (auto i : m_Services)
			{
				i->Cmd(wstrCmd, Cmds);
			}
		}

		for (auto i : m_Services)
		{
			i32Ret = i->Update();
			if (0 != i32Ret)
			{
				wstrOut = str(wformat(L"i32Ret=%1% serviceName=%2%")
					% i32Ret
					% i->Name()
					);
				D_Log(m_pLog, wstrOut.c_str());
				m_bQuit = true;
				break;
			}
		}

		if (m_pConsoleInput->IsQuit())
		{
			D_Log(m_pLog, L"已输入退出指令,正在退出中...");
			m_bQuit = true;
		}
	}

	if (!Uninit())
	{
		D_Log(m_pLog, L"Uninit fail");
	}
}

T_bool D_const
C_Global::Init(T_int32 argc, T_wchar* argv[])
{
	if (!InitLog()) { return false; };
	if (!InitTCP()) { return false; };
	if (!InitConsoleInput()) { return false; };
	if (!InitParam(argc, argv)) { return false; };
	if (!InitService()) { return false; };
	m_bQuit = false;
	return true;
}


T_bool D_const
C_Global::Uninit()
{
	if (!UninitService()) { return false; };
	if (!UnnitParam()) { return false; };
	if (!UninitConsoleInput()) { return false; };
	if (!UninitTCP()) { return false; };
	if (!UninitLog()) { return false; };
	return true;
}



T_bool D_const
C_Global::InitLog()
{
	m_pLog = D_N1(Log)::Create();
	m_pLog->Start();
	D_Log(m_pLog, L"C_Global::InitLog");
	return true;
}


T_bool D_const
C_Global::UninitLog()
{
	D_Log(m_pLog, L"C_Global::UninitLog");

	D_N1(Log)::Release(m_pLog);
	return true;
}



T_bool D_const
C_Global::InitParam(T_int32 argc, T_wchar* argv[])
{
	if (!ParamReg()) { return false; };

	namespace po = boost::program_options;
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, m_OD), vm);
	po::notify(vm);
	T_bool bFind = false;
	for (auto& v : m_TestFuncs)
	{
		if (vm.count(v.first))
		{
			v.second();
			bFind = true;
		}
	}
	if (!bFind)
	{
		cout << m_OD << endl;
	}

	return true;
}


T_bool D_const
C_Global::UnnitParam()
{
	D_Log(m_pLog, L"C_Global::UnnitParam");

	return true;
}


T_bool D_const
C_Global::InitService()
{
	D_Log(m_pLog, L"C_Global::InitService");

	if (!ServiceReg()) { return false; }
	if (!ServiceLoad()) { return false; }
	if (!ServiceCreate()) { return false; }
	if (!ServiceInit()) { return false; }

	return true;
}


T_bool D_const
C_Global::UninitService()
{
	D_Log(m_pLog, L"C_Global::UninitService");

	if (!ServiceUninit()) { return false; }
	if (!ServiceRelease()) { return false; }
	if (!ServiceFree()) { return false; }

	return true;
}



T_bool D_const
C_Global::ServiceReg()
{
	vector<wstring> ServiceNames;
	push_back(ServiceNames)
		(L"lib_bsn_service_template")
		(L"lib_bsn_service_tcp_server")
		;

	m_DynamicLibs.resize(ServiceNames.size(), T_nullptr);
	m_Services.resize(ServiceNames.size(), T_nullptr);
	for (size_t i = 0; i < ServiceNames.size(); ++i)
	{
		m_DynamicLibs[i] = D_N1(DynamicLib)::Create();
		m_DynamicLibs[i]->SetName(ServiceNames[i].c_str());
	}
	return true;
}


T_bool D_const
C_Global::ServiceLoad()
{
	D_Log(m_pLog, L"C_Global::ServiceLoad");

	wstring wstrOut;
	T_int32 i32Ret = 0;
	T_DynamicLib* pLib = T_nullptr;

	for (size_t i = 0; i < m_DynamicLibs.size(); ++i)
	{
		pLib = m_DynamicLibs[i];
		wstrOut = str(wformat(L"i=%1% LibName=%2% LibFileName=%3%")
			% i
			% pLib->LibName()
			% pLib->LibFileName()
			);
		D_Log(m_pLog, wstrOut.c_str());


		i32Ret = pLib->Load();
		if (0 != i32Ret)
		{
			wstrOut = str(wformat(L"i32Ret=%1% %2%")
				% i32Ret
				% pLib->Error(i32Ret)
				);
			D_Log(m_pLog, wstrOut.c_str());
			return false;
		}
	}
	return true;
}


T_bool D_const
C_Global::ServiceCreate()
{
	D_Log(m_pLog, L"C_Global::ServiceCreate");

	wstring wstrOut;
	T_int32 i32Ret = 0;
	I_Service::T_CreateFunc pFunc = T_nullptr;
	I_Service* pService = T_nullptr;
	T_DynamicLib* pLib = T_nullptr;

	for (size_t i = 0; i < m_DynamicLibs.size(); ++i)
	{
		pLib = m_DynamicLibs[i];
		wstrOut = str(wformat(L"i=%1% LibName=%2%")
			% i
			% pLib->LibName()
			);
		D_Log(m_pLog, wstrOut.c_str());

		pFunc = static_cast<I_Service::T_CreateFunc>(pLib->GetFunc(L"Create"));
		if (T_nullptr == pFunc)
		{
			D_Log(m_pLog, L"not found function Create");
			return false;
		}

		pService = pFunc();
		if (T_nullptr == pService)
		{
			D_Log(m_pLog, L"service create fail");
			return false;
		}
		m_Services[i] = pService;
	}

	return true;
}


T_bool D_const
C_Global::ServiceInit()
{
	D_Log(m_pLog, L"C_Global::ServiceInit");

	wstring wstrOut;
	T_int32 i32Ret = 0;
	I_Service* pService = T_nullptr;
	T_DynamicLib* pLib = T_nullptr;

	for (size_t i = 0; i < m_DynamicLibs.size(); ++i)
	{
		pLib = m_DynamicLibs[i];
		wstrOut = str(wformat(L"i=%1% LibName=%2%")
			% i
			% pLib->LibName()
			);
		D_Log(m_pLog, wstrOut.c_str());

		pService = m_Services[i];
		i32Ret = pService->Init(this);
		if (0 != i32Ret)
		{
			wstrOut = str(wformat(L"i32Ret=%1%") % i32Ret);
			D_Log(m_pLog, wstrOut.c_str());
			return false;
		}
	}

	return true;
}


T_bool D_const
C_Global::ServiceUninit()
{
	D_Log(m_pLog, L"C_Global::ServiceUninit");

	wstring wstrOut;
	T_int32 i32Ret = 0;
	I_Service* pService = T_nullptr;
	T_DynamicLib* pLib = T_nullptr;

	for (size_t i = 0; i < m_DynamicLibs.size(); ++i)
	{
		pLib = m_DynamicLibs[i];
		wstrOut = str(wformat(L"i=%1% LibName=%2%")
			% i
			% pLib->LibName()
			);
		D_Log(m_pLog, wstrOut.c_str());

		pService = m_Services[i];
		i32Ret = pService->Uninit();
		if (0 != i32Ret)
		{
			wstrOut = str(wformat(L"i32Ret=%1%") % i32Ret);
			D_Log(m_pLog, wstrOut.c_str());
			return false;
		}
	}

	return true;
}


T_bool D_const
C_Global::ServiceRelease()
{
	D_Log(m_pLog, L"C_Global::ServiceRelease");

	wstring wstrOut;
	T_int32 i32Ret = 0;
	I_Service::T_ReleaseFunc pFunc = T_nullptr;
	T_DynamicLib* pLib = T_nullptr;

	for (size_t i = 0; i < m_DynamicLibs.size(); ++i)
	{
		pLib = m_DynamicLibs[i];
		wstrOut = str(wformat(L"i=%1% LibName=%2%")
			% i
			% pLib->LibName()
			);
		D_Log(m_pLog, wstrOut.c_str());

		pFunc = static_cast<I_Service::T_ReleaseFunc>(pLib->GetFunc(L"Release"));
		if (T_nullptr == pFunc)
		{
			D_Log(m_pLog, L"not found function Release");
			return false;
		}

		pFunc(m_Services[i]);
		m_Services[i] = T_nullptr;
	}

	return true;
}

T_bool D_const
C_Global::ServiceFree()
{
	D_Log(m_pLog, L"C_Global::ServiceFree");

	wstring wstrOut;
	T_int32 i32Ret = 0;
	T_DynamicLib* pLib = T_nullptr;

	for (size_t i = 0; i < m_DynamicLibs.size(); ++i)
	{
		pLib = m_DynamicLibs[i];
		wstrOut = str(wformat(L"i=%1% LibName=%2%")
			% i
			% pLib->LibName()
			);
		D_Log(m_pLog, wstrOut.c_str());

		i32Ret = pLib->Free();
		if (0 != i32Ret)
		{
			wstrOut = str(wformat(L"i32Ret=%1% %2%")
				% i32Ret
				% pLib->Error(i32Ret)
				);
			D_Log(m_pLog, wstrOut.c_str());
			return false;
		}
	}
	return true;
}


T_bool D_const
C_Global::ParamReg()
{
	namespace po = boost::program_options;

	{
		// <command, description, function>
		typedef tuple<string, string, T_TestFunc> T_Confing;
		typedef vector<T_Confing> T_Configs;
		T_Configs Configs = tuple_list_of("test", "test", bind(&C_Global::Test, this))
			//("integer_traits", "integer_traits", integer_traits_)
			;

		// init test function
		for (auto& v : Configs)
		{
			insert(m_TestFuncs)(v.get<0>(), v.get<2>());
			m_ODTestFun.add_options()(v.get<0>().c_str(), v.get<1>().c_str());
		}
	}

	m_ODSystem.add_options()
		("help,h", "help message")
		;

	m_ODTest.add_options()
		("test_t,t", po::value<T_uint32>(&m_u32Test)->default_value(1), "test param")
		("ip", po::value<string>(&m_strIP), "ip as 192.168.199.111")
		("port", po::value<T_uint16>(&m_u16Port), "port as 50000")
		;

	m_OD.add(m_ODSystem).add(m_ODTestFun).add(m_ODTest);

	return true;
}


N_Bsn::T_void
C_Global::Test()
{
	D_Log(m_pLog, L"C_Global::Test");
}


T_bool D_const
C_Global::InitConsoleInput()
{
	D_Log(m_pLog, L"C_Global::InitConsoleInput");

	m_pConsoleInput = D_N1(ConsoleInput)::Create();
	m_pConsoleInput->Start();
	return true;
}


T_bool D_const
C_Global::UninitConsoleInput()
{
	D_Log(m_pLog, L"C_Global::UninitConsoleInput");
	if (!m_pConsoleInput->IsQuit())
	{
		D_Log(m_pLog, L"被动关闭,按Enter键继续...");
	}
	D_N1(ConsoleInput)::Release(m_pConsoleInput);
	return true;
}


T_bool D_const
C_Global::InitTCP()
{
	m_pTCP = D_N1(TCP)::Create();
	m_pTCP->Start();
	D_Log(m_pLog, L"C_Global::InitTCP");
	return true;
}


T_bool D_const
C_Global::UninitTCP()
{
	D_Log(m_pLog, L"C_Global::UninitTCP");

	D_N1(TCP)::Release(m_pTCP);
	return true;
}


I_Global::T_TCP*
C_Global::TCP()
{
	return m_pTCP;
}


I_Service*
C_Global::Service(T_uint32 D_const u32Index)
{
	return m_Services[u32Index];
}


I_Service*
C_Global::Service(T_wchar D_const * D_const pwcService)
{
	wstring wstrService(pwcService);
	for (auto i : m_Services)
	{
		if (wstrService.compare(i->Name()) == 0)
		{
			return i;
		}
	}

	return T_nullptr;
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
