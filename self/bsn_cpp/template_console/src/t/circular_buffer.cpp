#include <bsn/template_console/include/t/t.h>

T_void
circular_buffer_()
{
	typedef circular_buffer<int> T;
	auto funPrint = [](T& v){
		cout << endl;
		cout << "v.size()=" << v.size() << endl;
		cout << "v.capacity()=" << v.capacity() << endl;
		cout << "v.max_size()=" << v.max_size() << endl;
		cout << "v.empty()=" << v.empty() << endl;
		cout << "v.full()=" << v.full() << endl;
		copy(v.begin(), v.end(), std::ostream_iterator<int>(cout, " "));
		cout << endl;
	};

	{
		T cb(3);
		funPrint(cb);
	}
	{
		T cb = (list_of(1),2,3);
		funPrint(cb);
		cb.push_back(4);

		funPrint(cb);
		cb.push_front(5);
		funPrint(cb);
	}
}
