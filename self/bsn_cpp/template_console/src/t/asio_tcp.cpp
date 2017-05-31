#include <bsn/template_console/include/t/t.h>
#include <asio.hpp>
using namespace asio;


T_void
server()
{
	asio::io_service io;
	asio::ip::tcp::acceptor vAcceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 50000));
	cout << vAcceptor.local_endpoint().address() << endl;

	while (true)
	{
		asio::ip::tcp::socket vSocket(io);
		vAcceptor.accept(vSocket);
		cout << "client<:" << vSocket.remote_endpoint().address() << endl;
		vSocket.send(asio::buffer("hello asio"));
	}
}

T_void
client()
{
	asio::io_service io;
	asio::ip::tcp::endpoint ep(asio::ip::address::from_string("127.0.0.1"), 50000);
	asio::ip::tcp::socket vSocket(io);
	vSocket.connect(ep);
	cout << vSocket.local_endpoint().address() << endl;
	cout << "vSocket.available()=" << vSocket.available() << endl;
	array<char, 512> vData;
	vSocket.receive(asio::buffer(vData));
	cout << "receive from:" << vSocket.remote_endpoint().address() << endl;
	cout << &vData[0] << endl;
}

T_void
asio_tcp()
{
	boost::thread t1(server);
	boost::this_thread::sleep_for(boost::chrono::seconds(1));
	boost::thread t2(client);
	t2.join();

	{
		boost::scoped_thread<boost::detach> st(client);
	}
	{
		boost::scoped_thread<> st(client);
	}
	boost::thread t3(client);
	t3.join();
}
