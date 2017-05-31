#include <bsn/template_console/include/t/t.h>
#include <bsn/template_console/include/global.h>

C_Global* g = T_nullptr;
namespace po = boost::program_options;


T_bool D_const
C_Global::Init(T_int32 argc, T_wchar* argv[])
{
	m_pLog = D_N1(Log)::Create();
	m_pLog->Start();
	m_pLog->Write(1, L"C_Global::Init");

	InitParam();
	ProcParam(argc, argv);

	return true;
}


T_bool D_const
C_Global::Release()
{
	D_N1(Log)::Release(m_pLog);
	return true;
}


T_bool D_const
C_Global::ProcParam(T_int32 argc, T_wchar* argv[])
{
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, m_OD), vm);
	po::notify(vm);
	T_bool bFind = false;
	for (auto& v : g->m_TestFuncs)
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

	/*if (vm.count("ip"))
	{
	cout << "ip was set to " << vm["ip"].as<string>() << "." << endl;
	}
	else
	{
	cout << "ip was not set." << endl;
	return;
	}
	wstring wstrIP;
	D_N2(Common, String)::ANSI2Unicode(vm["ip"].as<string>(), wstrIP);

	if (vm.count("port"))
	{
	cout << "port was set to " << vm["port"].as<T_uint16>() << "." << endl;
	}
	else
	{
	cout << "port was not set." << endl;
	return;
	}
	*/

	return true;
}



C_Global::C_Global()
	: m_ODSystem("System")
	, m_ODTest("Test")
	, m_ODTestFun("TestFun")
	, m_pLog( T_nullptr )
{

}


T_bool D_const
C_Global::InitParam()
{
	{
		// <command, description, function>
		typedef tuple<string, string, T_TestFunc> T_Confing;
		typedef vector<T_Confing> T_Configs;
		T_Configs Configs = tuple_list_of("test", "test", test)
			("condition_variable_any", "condition_variable_any", condition_variable_any_)
			("thread_call_once", "thread_call_once", thread_call_once)
			("asio_tcp_aysnc", "asio_tcp_aysnc", asio_tcp_aysnc)
			("asio_tcp", "asio_tcp", asio_tcp)
			("asio_signal_set", "asio_signal_set", asio_signal_set)
			("date_time", "date_time", date_time_)
			("progress", "progress", progress)
			("asio_steady_timer", "asio_steady_timer", asio_steady_timer)
			("virtual", "virtual", virtual_)
			("circular_buffer", "circular_buffer", circular_buffer_)
			("assign", "assign", assign_)
			("random", "random", random_)
			("ratio", "ratio", ratio_)
			("multiprecision", "big value", multiprecision_)
			("math_constants", "math constants", math_constants)
			("atomic", "atomic", atomic_)
			("crc", "crc", crc_)
			("t_udp_Server", "t_udp_Server", t_udp_Server)
			("t_tcp_Server", "t_tcp_Server", t_tcp_Server)
			("t_udp_Client", "t_udp_Client", t_udp_Client)
			("t_tcp_Client", "t_tcp_Client", t_tcp_Client)
			("integer_traits", "integer_traits", integer_traits_)
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


T_void 
C_Global::Run(T_int32 argc, T_wchar* argv[])
{
	Init(argc, argv);
	{// Ìí¼Ó´úÂë
	
	}
	Release();
}
