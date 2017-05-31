#include <bsn/udp_t/include/main.h>
#include <bsn/include/port.h>
#include <bsn/common/include/port.h>
#include <bsn/udp/include/port.h>

using namespace N_Bsn;
//////////////////////////////////////////////////////////////////////////
T_void
Server(T_wchar D_const * D_const pwcIP, T_uint16 D_const u16Port)
{
	using namespace D_N1(UDP);
	I_Interface* pInterface = Create();
	wcout << pInterface->Name() << endl;
	T_int32 nRet = pInterface->Bind(pwcIP, u16Port);
	if (0 != nRet)
	{
		wcout << pInterface->Error(nRet) << endl;
		return;
	}
	T_byte byData[1024];
	size_t stLen = 0;
	while (true)
	{
		pInterface->Recv(byData, 1024, stLen);
		cout << "stLen= " << stLen << endl;
		pInterface->Send(byData, stLen, stLen);
		cout << "stLen= " << stLen << endl;
	}
	Release( pInterface );
}


T_void
Client(T_wchar D_const * D_const pwcIP, T_uint16 D_const u16Port)
{
	using namespace D_N1(UDP);
	I_Interface* pInterface = Create();
	wcout << pInterface->Name() << endl;
	T_byte byData[1024];
	size_t stLen = 0;
	T_int32 nRet = pInterface->Bind(T_nullptr, 0);
	if (0 != nRet)
	{
		wcout << nRet << pInterface->Error(nRet) << endl;
		return;
	}
	{
		nRet = pInterface->SetSendDes(pwcIP, u16Port);
		if (0 != nRet)
		{
			wcout << nRet << pInterface->Error(nRet) << endl;
			return;
		}
		string strSend("hello world!");
		cout << strSend.c_str() << " " << strSend.size() << endl;
		nRet = pInterface->Send((T_byte*)strSend.c_str(), strSend.size(), stLen);
		if (0 != nRet)
		{
			wcout << nRet << pInterface->Error(nRet) << endl;
			return;
		}
		cout << "stLen= " << stLen << endl;
		
		nRet = pInterface->Recv(byData, 1024, stLen);
		if (0 != nRet)
		{
			wcout << nRet << pInterface->Error(nRet) << endl;
			return;
		}
		cout << "stLen= " << stLen << endl;
		
		byData[stLen] = 0;
		cout << (T_char*)byData << endl;
	}
	Release(pInterface);
}


T_void
Params(T_int32 argc, T_wchar* argv[])
{
	/*
	bsn_2_udp_t_d.exe -s --ip 127.0.0.1 --port 50000
	bsn_2_udp_t_d.exe  --ip 127.0.0.1 --port 50000
	*/
	namespace po = boost::program_options;
	int n32Test = 0;
	po::options_description od("Allowed options");
	od.add_options()
		("help,h", "help message")
		("test,t", po::value<T_int32>(&n32Test)->default_value(1), "test param")

		("server,s", "open server")
		("ip", po::value<string>(), "ip as 192.168.199.111")
		("port", po::value<T_uint16>(), "port as 50000")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, od), vm);
	po::notify(vm);
	if (vm.count("help"))
	{
		cout << od << endl;
		return;
	}

	if (vm.count("ip"))
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

	if (vm.count("server"))
	{
		Server(wstrIP.c_str(), vm["port"].as<T_uint16>());
	}
	else
	{
		Client(wstrIP.c_str(), vm["port"].as<T_uint16>());
	}
}


T_void
Test(T_int32 argc, T_wchar* argv[])
{
	{
		string strIn("a b c");
		string strSep(" ");
		vector<string> vecOut;
		D_N1(String)::Split(strIn, strSep, vecOut);
		for (auto i : vecOut)
		{
			cout << i << endl;
		}
	}

	{
		using namespace D_N2(Common, OS);
		wcout << Type2Wstr( Type() ) << endl;
	}
}

T_int32 
wmain(T_int32 argc, T_wchar* argv[])
{
	setlocale(LC_ALL, "chs"); 

	{// 添加代码
		Params(argc, argv);
	}

	wcout << L"要退出了" << endl;
	system("pause");
	return 0;
}









