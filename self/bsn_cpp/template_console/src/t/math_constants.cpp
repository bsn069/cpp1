#include <bsn/template_console/include/t/t.h>

T_void
math_constants()
{
	wcout << std::setprecision(100);
	wcout << L"float_constants::pi=         " << float_constants::pi << endl;
	wcout << L"double_constants::pi=        " << double_constants::pi << endl;
	wcout << L"long_double_constants::pi=   " << long_double_constants::pi << endl;

	wcout << L"float_constants::e=         " << float_constants::e << endl;
	wcout << L"double_constants::e=        " << double_constants::e << endl;
	wcout << L"long_double_constants::e=   " << long_double_constants::e << endl;

	wcout << L"constants::pi<float>()=         " << constants::pi<float>() << endl;
	wcout << L"constants::pi<double>()=        " << constants::pi<double>() << endl;


	typedef cpp_dec_float_100 float_100;
	cout << std::setprecision(std::numeric_limits<float_100>::digits10);
	cout << "constants::pi<float_100>()=        " << constants::pi<float_100>() << endl;
}
