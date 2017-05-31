#include <bsn/template_console/include/t/t.h>

T_void
ratio_()
{
	using namespace boost;
	{
		typedef ratio<1, 2> half;
		cout << half::num << endl;
		cout << half::den << endl;
		cout << half::value() << endl;
	}
	{
		cout << kibi::num << endl;
		cout << kibi::den << endl;
		cout << kibi::value() << endl;
	}
	{
		cout << ratio_string<kibi, char>::short_name() << endl;
		cout << ratio_string<kibi, char>::long_name() << endl;

		wcout << ratio_string<kibi, T_wchar>::short_name() << endl;
		wcout << ratio_string<kibi, T_wchar>::long_name() << endl;
	}
}
