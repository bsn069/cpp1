#include "./main.h"
#include "./session.h"
D_BsnNamespace1(TCP)
//////////////////////////////////////////////////////////////////////


T_int32 D_const
C_Session::SetUserData(T_void* pUserData)
{
	m_pUserData = pUserData;
	return 0;
}


T_int32 D_const
C_Session::GetUserData(T_void*& pUserData) D_const
{
	pUserData = m_pUserData;
	return 0;
}



C_Session::C_Session(asio::io_service& IOService)
	: m_Socket( IOService )
	, m_pUserData( T_nullptr )
	, m_pLastRecvBuffers( T_nullptr )
	, m_State( S_Close )
{

}


T_int32 D_const
C_Session::Close()
{
	if (IsClose())
	{
		return -8;
	}
	InterlockedExchange((LONG volatile*)&m_State, S_Close);
	asio::error_code ec;
	m_Socket.close(ec);
	if (ec)
	{
		cout << ec.message() << endl;
	}
	return 0;
}


N_Bsn::T_void
C_Session::PostRead()
{
	asio::detail::transfer_at_least_t vtransfer_at_least_t = asio::transfer_at_least(1);

	T_Buffer* pBuffer = New<T_Buffer>();
	async_read(
		m_Socket
		, asio::buffer(pBuffer->Data(), pBuffer->MaxSize())
		, vtransfer_at_least_t
		, boost::bind(
			&C_Session::OnRead
			, shared_from_this()
			, pBuffer
			, asio::placeholders::error
			, asio::placeholders::bytes_transferred
			)
		);
}


N_Bsn::T_void
C_Session::OnRead(I_Buffer* pData, asio::error_code D_const& error, size_t D_const bytes_transferred)
{
	if (error)
	{
		cout << error.message() << endl;
		Close();
		Delete(pData);
		return;
	}

	pData->Len() = bytes_transferred;
	m_Buffers.Write(pData);
	PostRead();
}


T_int32 D_const
C_Session::Recv(T_Buffers*& pBuffers)
{
	if (T_nullptr != m_pLastRecvBuffers)
	{
		for (auto i : *m_pLastRecvBuffers)
		{
			Delete(i);
		}
	}
	m_pLastRecvBuffers = &(m_Buffers.Flip());
	pBuffers = m_pLastRecvBuffers;
	return 0;
}


T_int32 D_const
C_Session::Send(T_byte* pData, T_uint32 u32Len)
{
	if (!IsConnected())
	{
		return -9;
	}

	T_byte* p = Malloc<T_byte>(u32Len);
	async_write(
		m_Socket,
		asio::buffer(p, u32Len),
		bind(
			&C_Session::OnSend
			, shared_from_this()
			, p
			, asio::placeholders::error
			, asio::placeholders::bytes_transferred
			)
		);
	return 0;
}


N_Bsn::T_void
C_Session::OnSend(T_byte* pData, asio::error_code D_const& error, size_t D_const bytes_transferred)
{
	Free(pData);

	if (error)
	{
		cout << error.message() << endl;
		Close();
	}
}



C_Session::~C_Session()
{
	T_Buffers* pBuffers;
	Recv(pBuffers);
	Recv(pBuffers);
}

 


T_int32 D_const
C_Session::GetRemoteIP(T_wchar D_const *& pwcIP) D_const
{
	pwcIP = m_wstrRemoteIP.c_str();
	return 0;
}

 


T_int32 D_const
C_Session::GetRemotePort(T_uint16& u16Port) D_const
{
	u16Port = m_u16RemotePort;
	return 0;
}


T_int32 D_const
C_Session::GetLocalIP(wstring& wstrIP) 
{
	if (!IsConnected())
	{
		return -9;
	}

	D_N2(Common, String)::ANSI2Unicode(
	m_Socket.local_endpoint().address().to_v4().to_string().c_str()
	, wstrIP
	);
	return 0;
}


T_int32 D_const
C_Session::GetLocalPort(T_uint16& u16Port) 
{
	if (!IsConnected())
	{
		return -9;
	}

	u16Port = m_Socket.local_endpoint().port();
	return 0;
}


T_bool D_const
C_Session::IsClose() 
{
	return (S_Close == State());
}


T_bool D_const
C_Session::IsConnected() 
{
	return (S_Established == State());
}


C_Session::E_State D_const
C_Session::State()
{
	return (E_State)InterlockedExchangeAdd((LONG volatile*)&m_State, 0);
}


 

D_BsnNamespace1End
