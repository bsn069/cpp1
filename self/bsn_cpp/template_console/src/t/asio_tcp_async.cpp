#include <bsn/template_console/include/t/t.h>
#include <asio.hpp>
using namespace asio;

typedef asio::ip::tcp::acceptor T_Acceptor;
typedef asio::ip::tcp::endpoint T_Endpoint;
typedef asio::ip::tcp::socket T_Socket;
typedef boost::shared_ptr<T_Socket> T_SocketPtr;

class C_Server
{
public:
	T_void Accept();
	T_void AcceptHandle(asio::error_code D_const& ec, T_SocketPtr vSocketPtr);
	T_void WriterHandle(asio::error_code D_const& ec, size_t stLen);
	T_void Run();

public:
	C_Server();
	~C_Server();

public:
	asio::io_service	m_io;
	T_Acceptor			m_Acceptor;
};

C_Server::C_Server()
	: m_Acceptor(m_io, T_Endpoint(ip::tcp::v4(), 50000))
{
	Accept();
}

C_Server::~C_Server()
{
}


N_Bsn::T_void
C_Server::Accept()
{
	T_SocketPtr vSocketPtr(new T_Socket(m_io));
	m_Acceptor.async_accept(*vSocketPtr, bind(&C_Server::AcceptHandle, this, asio::placeholders::error, vSocketPtr));
}


N_Bsn::T_void
C_Server::AcceptHandle(asio::error_code D_const& ec, T_SocketPtr vSocketPtr)
{
	if (ec)
	{
		cout << ec.message() << endl;
		return;
	}

	cout << "client:" << vSocketPtr->remote_endpoint().address() << endl;
	vSocketPtr->async_send(asio::buffer("hello asio"), bind(&C_Server::WriterHandle, this, asio::placeholders::error, asio::placeholders::bytes_transferred));

	Accept();
}


N_Bsn::T_void
C_Server::WriterHandle(asio::error_code D_const& ec, size_t stLen)
{
	if (ec)
	{
		cout << ec.message() << endl;
		return;
	}
	cout << "stLen=" << stLen << endl;
}


N_Bsn::T_void
C_Server::Run()
{
	boost::thread_group	vThreadGroup;

	for (auto i = 0; i < 2; ++i)
	{
		vThreadGroup.create_thread(bind(&asio::io_service::run, &m_io));
	}
	vThreadGroup.join_all();
}

static
T_void
server()
{
	C_Server vServer;
	vServer.Run();
}

static
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
	asio::error_code ec;
	vSocket.read_some(asio::buffer(vData), ec);
	if (ec)
	{
		cout << ec.message() << endl;
		return;
	}
	cout << "receive from:" << vSocket.remote_endpoint().address() << endl;
	cout << &vData[0] << endl;
}

T_void
asio_tcp_aysnc()
{
	boost::thread t1(server);
	boost::this_thread::sleep_for(boost::chrono::seconds(2));
	
	boost::thread_group	vThreadGroup;
	for (auto i = 0; i < 20; ++i)
	{
		vThreadGroup.create_thread(client);
	}
	vThreadGroup.join_all();
}
