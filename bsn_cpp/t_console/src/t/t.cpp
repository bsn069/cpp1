#include <bsn/template_console/include/t/t.h>
#include <bsn/template_console/include/global.h>

T_void
test()
{
	g->m_u32Test = 2;

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
	{
		cout << std::hex;
		using boost::algorithm::hex;
		using boost::algorithm::unhex;

		int iIn[] = {1,0x1234abcd,0};
		std::for_each(iIn, iIn + D_ArrayCount(iIn), [](int i){cout << i << endl; });

		string vecOut;
		hex(iIn, std::back_inserter(vecOut));
		cout << vecOut << endl;

		vector<int> vecOut2;
		unhex(vecOut, std::back_inserter(vecOut2));
		BOOST_FOREACH(auto i, vecOut2)
		{
			printf("%X\n", i);
		}
	}
}
