#pragma once

class FBNETWORK_API CFBNetwork_T_Dg : public CFBNetwork_Dg
{
public:
	enum OP
	{
		OP_CONNECT		= 0,
		OP_ACCEPT,
		OP_SEND,
		OP_RECV,
	};
	enum
	{
		BUF_SIZE		= 1024,
	};
 
public:
	WSAOVERLAPPED						m_Overlapped;
	WSABUF								m_Buffer;
	char								m_pBuffer[BUF_SIZE];
	OP									m_OP;

public:
										CFBNetwork_T_Dg()
	{
		ZeroMemory(&m_Overlapped, sizeof(m_Overlapped));
		m_Buffer.len = 0;
		m_Buffer.buf = m_pBuffer;
	}
	virtual								~CFBNetwork_T_Dg()
	{
	}

	virtual DWORD						DataLen(void)
	{
		return m_Buffer.len;
	}
	virtual char*						Data(void)
	{
		return m_pBuffer;
	}
};