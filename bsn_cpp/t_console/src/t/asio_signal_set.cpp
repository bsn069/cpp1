#include <bsn/template_console/include/t/t.h>
#include <boost/asio.hpp>
using namespace boost::asio;


T_void
asio_signal_set()
{
	io_service io;
	signal_set sig(io, SIGINT);
	sig.add(SIGBREAK);
	typedef void(handle_type)(boost::system::error_code D_const&, int);

	function<handle_type> handle1 =
		[&](boost::system::error_code D_const& ec, int n){
		if (ec)
		{
			cout << ec.message() << endl;
			return;
		}
		sig.async_wait(handle1);
		if (n != SIGINT)
		{
			return;
		}
		cout << "SIGINT ctrl+c" << endl;
	};

	function<handle_type> handle2 = 
		[&](boost::system::error_code D_const& ec, int n)
		{
			if (ec)
			{
				cout << ec.message() << endl;
				return;
			}
			sig.async_wait(handle2);

			if (n != SIGBREAK)
			{
				return;
			}
			cout << "SIGBREAK ctrl + break" << endl;
		};

	sig.async_wait(handle2);
	sig.async_wait(handle1);
	io.run();
}
