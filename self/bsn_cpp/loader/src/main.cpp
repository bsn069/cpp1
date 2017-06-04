#include "./main.h"


T_int32 
wmain(T_int32 argc, T_wchar* argv[])
{
	setlocale(LC_ALL, "chs"); 

	{
		using namespace D_N1(Global);
		D_N1(Other)::I_Global* pGlobal = Create();
		pGlobal->Wmain(argc, argv);
		Release(pGlobal);
	}

	wcout << L"已退出" << endl;
	system("pause");
	return 0;
}









