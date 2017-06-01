#include <bsn/template_console/include/t/t.h>
#include <boost/asio/system_timer.hpp>
#include <boost/progress.hpp>
using namespace boost::chrono;
using namespace boost::asio;

T_void
progress()
{
	io_service io;
	{
		cout << endl;
		cout << "progress_display" << endl;
		boost::progress_display t(10000);
		{
			for (auto i = 0; i < 10000; ++i)
			{
				Sleep(1);
				++t;
			}
			system_timer t(io, seconds(1));
			t.wait();
		}
	}
	{
		boost::progress_timer t;
		cout << endl;
		cout << "progress_timer" << endl;
		{
			system_timer t(io, seconds(1));
			t.wait();
		}
	}
}
