#include <boost/program_options.hpp>
#include <stdint.h>
#include <locale.h>
#include <iostream>

int 
main(int argc, char* argv[])
{
	setlocale(LC_ALL, "chs"); 

	// {
	// 	g = New<C_Global>();
	// 	g->Run(argc, argv);
	// 	Delete(g);
	// }

	std::cout << "要退出了" << std::endl;
	// system("pause");
	int t;
	std::cin >> t;
	return 0;
}









