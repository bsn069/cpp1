#include <bsn/template_console/include/t/t.h>

T_void
multiprecision_()
{
	{
		typedef cpp_dec_float_100 float_100;
		cout << std::setprecision(std::numeric_limits<float_100>::digits10);
		cout << "constants::pi<float_100>()=        " << constants::pi<float_100>() << endl;
		cout << "constants::pi<float_100>()=        " << constants::pi<float_100>() + constants::pi<float_100>() << endl;
	}
	{
		typedef number<cpp_dec_float<20> > float_20;
		cout << std::setprecision(std::numeric_limits<float_20>::digits10);
		cout << "constants::pi<float_20>()=        " << constants::pi<float_20>() << endl;
		cout << "constants::pi<float_20>()=        " << constants::pi<float_20>() + constants::pi<float_20>() << endl;
		float_20 a("1234567890123456789012345678901234567890");
		float_20 b = a + a;
		cout << "float_20=        " << a << endl;
		cout << "float_20=        " << b << endl;
	}
	{
		typedef number<cpp_int_backend<99, 99, unsigned_magnitude, unchecked, void> > uint_99;
		cout << std::setprecision(std::numeric_limits<uint_99>::digits10);
		uint256_t a("1234567890123456789012345678901234567890");
		uint1024_t b = a + a;
		cout << "uint1024_t=        " << a << endl;
		cout << "uint1024_t=        " << b << endl;
	}
}

