#pragma once
D_BsnNamespace1(TCP)
//////////////////////////////////////////////////////////////////////


class I_Session
{
public:
	typedef shared_ptr<I_Session> T_Ptr;
	typedef vector<T_Ptr> T_Ptrs;
	typedef vector<I_Buffer*> T_Buffers;


protected:
	virtual ~I_Session() {};


public:
	virtual T_int32 D_const SetUserData(T_void* pUserData) = 0;
	virtual T_int32 D_const GetUserData(T_void*& pUserData) D_const = 0;

	virtual T_int32 D_const Close() = 0;
	virtual T_bool D_const	IsClose()  = 0;
	virtual T_bool D_const	IsConnected()  = 0;

	virtual T_int32 D_const Recv(T_Buffers*& pBuffers) = 0;
	virtual T_int32 D_const Send(T_byte* pData, T_uint32 u32Len) = 0;

	virtual T_int32 D_const GetRemoteIP(T_wchar D_const *& pwcIP) D_const  = 0;
	virtual T_int32 D_const GetRemotePort(T_uint16& u16Port) D_const  = 0;

	virtual T_int32 D_const GetLocalIP(wstring& wstrIP)   = 0;
	virtual T_int32 D_const GetLocalPort(T_uint16& u16Port)   = 0;
};


class I_OnSession
{
public:
	typedef T_uint32 T_ID;

public:
	virtual T_int32 D_const	GetSessions(I_Session::T_Ptrs*& pSessions) = 0;

	T_void			SetID(T_ID ID){ m_ID = ID;};
	T_ID D_const	GetID() D_const {return m_ID;};


protected:
	I_OnSession()
		: m_ID(0)
	{
	};
	virtual ~I_OnSession() {};

protected:
	T_ID m_ID;
};


class I_Server : public I_OnSession
{
public:
 

protected:
	virtual ~I_Server() {};


public:
	virtual T_int32 D_const Bind(
		T_wchar D_const * D_const	pwcIP
		, T_uint16 D_const			u16Port
		) = 0;
	virtual T_int32 D_const Listen() = 0;
	virtual T_int32 D_const StopListen() = 0;
};


class I_Client : public I_OnSession
{
public:
 

protected:
	virtual ~I_Client() {};


public:
	virtual T_int32 D_const Connect(
		T_wchar D_const * D_const	pwcIP
		, T_uint16 D_const			u16Port
		, T_void*					pUserData
		) = 0;
};


class I_Interface
{
public:


protected:
	virtual ~I_Interface() {};


public:
	virtual T_wchar D_const * D_const Name() D_const = 0;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const = 0;

	virtual T_int32 D_const CreateServer(I_Server*& pServer) = 0;
	virtual T_int32 D_const ReleaseServer(I_Server*& pServer) = 0;

	virtual T_int32 D_const CreateClient(I_Client*& pClient) = 0;
	virtual T_int32 D_const ReleaseClient(I_Client*& pClient) = 0;

	virtual T_int32 D_const Start() = 0;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


