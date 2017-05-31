#pragma once

class CFBNetwork_U_Dg : public CFBNetwork_Dg, public CFBKernel_List_Node<CFBNetwork_U_Dg>
{
public:
	enum
	{
		TOTALSIZE		= 1024,
		HEADERSIZE		= sizeof(DWORD) + sizeof(DWORD) + sizeof(DWORD),
		BUFFERSIZE		= TOTALSIZE - HEADERSIZE,
	};
	enum
	{
		OPEN			= 0,
		CLOSE			= 1,
		SEQ				= 2,
		ACK				= 3,
		WND				= 4,
	};

public:
	#pragma pack(1)
	/*
	 0                   1                   2                   3
	 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	|m|u|                          ID                               |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	|                       Sequence Number                         |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	| fff |                Receive Window Size                      |
	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	
	bit m:
		0:	P2P
		1:	CS

	bit u:
		if m == 0
			0:	Peer 0
			1:	Peer 1
		else if m == 1
			0:	Client Side
			1:	Server Side

	bit fff:
		000: OPEN
		001: CLOSE
		010: SEQ
		011: ACK
		100: WND
	*/
	struct Content
	{
		DWORD					m_dwID;							// ID
		DWORD					m_dwSEQ;						// ���к�
		DWORD					m_dwWnd;						// ��־�ͻ������ڳߴ�
		char					m_pData[BUFFERSIZE];			// ����
	};
	#pragma pack()

public:
	DWORD						m_dwLen;						// �������ĳ���
	Content						m_Content;						// ��������

	double						m_dResendTimer;					// ���·��ͼ�ʱ��

public:
	CFBNetwork_U_Dg()
	{
		m_dwLen = HEADERSIZE;
		m_dResendTimer = 0.0;
	}

	void SetFlagWnd(DWORD dwFlag, DWORD dwWnd)
	{
		m_Content.m_dwWnd = (dwFlag << 29) | dwWnd;

		// ACK��һ��SACK
		if(dwFlag == ACK)
		{
			m_dwLen += sizeof(DWORD);
		}
	}
	DWORD Flag(void)
	{
		return m_Content.m_dwWnd >> 29;
	}
	DWORD Wnd(void)
	{
		return m_Content.m_dwWnd << 3 >> 3;
	}
	virtual DWORD DataLen(void)
	{
		return m_dwLen - HEADERSIZE;
	}
	virtual char* Data(void)
	{
		return m_Content.m_pData;
	}
};