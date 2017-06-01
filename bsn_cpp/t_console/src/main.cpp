#include <bsn/template_console/include/global.h>


T_int32 
wmain(T_int32 argc, T_wchar* argv[])
{
	setlocale(LC_ALL, "chs"); 

	{
		g = New<C_Global>();
		g->Run(argc, argv);
		Delete(g);
	}

	wcout << L"ÒªÍË³öÁË" << endl;
	system("pause");
	return 0;
}









