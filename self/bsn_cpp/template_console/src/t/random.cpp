#include <bsn/template_console/include/t/t.h>

T_void
random_()
{
	using namespace boost;
	{
		mt19937 rng(1);
		cout << "mt19937::min()=" << mt19937::min() << endl;
		cout << "mt19937::max()=" << mt19937::max() << endl;
		for (auto i = 0; i < 5; ++i)
		{
			cout << rng() << endl;
		}
	}
	{
		mt19937 rng(1);
		for (auto i = 0; i < 2; ++i)
		{
			cout << rng() << endl;
		}
		cout << "rng.discard(1)" << endl;
		rng.discard(1);
		for (auto i = 0; i < 2; ++i)
		{
			cout << rng() << endl;
		}
	}
	{
		mt19937 rng(time(0));
		vector<int> vecOut(10);
		rng.generate(vecOut.begin(), vecOut.end());
		for (auto i:vecOut)cout << i << endl;
	}
	{
		cout << "random::uniform_int_distribution" << endl;
		mt19937 rng(1);
		uniform_int_distribution<> ui(0, 5);
		for (auto i = 0; i < 5; ++i)
		{
			cout << ui(rng) << endl;
		}
	}
	{
		cout << "random::uniform_01" << endl;
		mt19937 rng(1);
		uniform_01<> ui;
		for (auto i = 0; i < 5; ++i)
		{
			cout << ui(rng) << endl;
		}
	}
	{
		cout << "random::normal_distribution 均值1 方差2" << endl;
		mt19937 rng(1);
		normal_distribution<> ui(1,2);
		for (auto i = 0; i < 5; ++i)
		{
			cout << ui(rng) << endl;
		}
	}
	{
		cout << "variate_generator random::normal_distribution 均值1 方差2" << endl;
		mt19937 rng(1);
		normal_distribution<> ui(1, 2);
		variate_generator<mt19937, normal_distribution<>> gen(rng, ui);
		for (auto i = 0; i < 5; ++i)
		{
			cout << gen() << endl;
		}
	}
}
