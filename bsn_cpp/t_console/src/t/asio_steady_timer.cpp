#include <bsn/template_console/include/t/t.h>
#include <boost/asio/system_timer.hpp>
#include <boost/timer/timer.hpp>
using namespace boost::chrono;
using namespace boost::asio;
using namespace boost::timer;




T_void
asio_steady_timer()
{
	io_service io;
	boost::timer::auto_cpu_timer act;
	{
		cout << endl;
		cout << "async_wait" << endl;
		steady_clock::time_point start = steady_clock::now();
		cout << "start=" << start << endl;
		{
			system_timer t(io, milliseconds(1500));
			t.async_wait([](boost::system::error_code D_const& ec){cout << "t.async_wait" << endl; });
			io.run();
		}
		steady_clock::time_point end = steady_clock::now();
		cout << "end=  " << end << endl;
		duration<double> sec = end - start;
		cout << " sec.count()= " << sec.count() << endl;
	}
	{
		cout << endl;
		cout << "thread_clock" << endl;
		thread_clock::time_point start = thread_clock::now();
		cout << "start=" << start << endl;
		{
			system_timer t(io, seconds(1));
			t.wait();
		}
		thread_clock::time_point end = thread_clock::now();
		cout << "end=  " << end << endl;
		duration<double> sec = end - start;
		cout << " sec.count()= " << sec.count() << endl;
	}
	act.stop();
	{
		cout << endl;
		cout << "process_cpu_clock" << endl;
		process_cpu_clock::time_point start = process_cpu_clock::now();
		cout << "start=" << start << endl;
		{
			system_timer t(io, seconds(1));
			t.wait();
		}
		process_cpu_clock::time_point end = process_cpu_clock::now();
		cout << "end=  " << end << endl;
		duration<double> sec = end - start;
		cout << " sec.count()= " << sec.count() << endl;
	}
	act.resume();
	{
		cout << endl;
		cout << "process_real_cpu_clock" << endl;
		process_real_cpu_clock::time_point start = process_real_cpu_clock::now();
		cout << "start=" << start << endl;
		{
			system_timer t(io, seconds(1));
			t.wait();
		}
		process_real_cpu_clock::time_point end = process_real_cpu_clock::now();
		cout << "end=  " << end << endl;
		duration<double> sec = end - start;
		cout << " sec.count()= " << sec.count() << endl;
	}
	{
		cout << endl;
		cout << "process_system_cpu_clock" << endl;
		process_system_cpu_clock::time_point start = process_system_cpu_clock::now();
		cout << "start=" << start << endl;
		{
			system_timer t(io, seconds(1));
			t.wait();
		}
		process_system_cpu_clock::time_point end = process_system_cpu_clock::now();
		cout << "end=  " << end << endl;
		duration<double> sec = end - start;
		cout << " sec.count()= " << sec.count() << endl;
	}
	{
		cout << endl;
		cout << "process_user_cpu_clock" << endl;
		process_user_cpu_clock::time_point start = process_user_cpu_clock::now();
		cout << "start=" << start << endl;
		{
			system_timer t(io, seconds(1));
			t.wait();
		}
		process_user_cpu_clock::time_point end = process_user_cpu_clock::now();
		cout << "end=  " << end << endl;
		duration<double> sec = end - start;
		cout << " sec.count()= " << sec.count() << endl;
	}
	{
		cout << endl;
		cout << "system_clock" << endl;
		system_clock::time_point start = system_clock::now();
		cout << "start=" << start << endl;
		{
			system_timer t(io, seconds(1));
			t.wait();
		}
		system_clock::time_point end = system_clock::now();
		cout << "end=  " << end << endl;
		duration<double> sec = end - start;
		cout << " sec.count()= " << sec.count() << endl;
		cout << "system_clock::to_time_t(start)=" << system_clock::to_time_t(start) << endl;
		cout << "system_clock::to_time_t(end)=  " << system_clock::to_time_t(end) << endl;
	}
	{
		cout << endl;
		cout << "steady_clock" << endl;
		steady_clock::time_point start = steady_clock::now();
		cout << "start=" << start << endl;
		{
			steady_timer t(io, seconds(1));
			t.wait();
		}
		steady_clock::time_point end = steady_clock::now();
		cout << "end=  " << end << endl;
		duration<double> sec = end - start;
		cout << " sec.count()= " << sec.count() << endl;
	}

	cout << endl;
	//act.report();
}
