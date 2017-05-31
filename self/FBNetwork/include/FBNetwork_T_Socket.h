#pragma once

class CFBNetwork_T;

// �����������̰߳�ȫ��
class FBNETWORK_API CFBNetwork_T_Socket
{
public:
	enum STATE
	{
		S_CLOSE							= 0,
		S_CONNECTING,
		S_ESTABLISHED,
	};

public:
	CFBNetwork_T*							m_pT;
	SOCKET									m_Socket;						// socket

	// ���ص�ַ
	union 
	{
		BYTE								m_byIP[4];
		DWORD								m_dwIP;
	}										m_LocalIP;
	WORD									m_wLocalPort;
	// Զ�˵�ַ
	union 
	{
		BYTE								m_byIP[4];
		DWORD								m_dwIP;
	}										m_RemoteIP;
	WORD									m_wRemotePort;

	
	STATE									m_State;						// ״̬

	//HANDLE								m_hAcceptThread;
	//HANDLE								m_pAcceptExEvent[2];
	//DWORD									m_dwAcceptExs;

	CFBKernel_Double<CFBNetwork_T_Socket*>	m_Accepts;						// �½��ܵ�����
	CFBKernel_Double<CFBNetwork_T_Dg*>		m_Dgs;							// ���Թ��ϲ��ȡ��Dg

	DWORD									m_dwUses;						// ��ʹ�õĴ���

	CFBKernel_Mutex 						m_Mutex;

	LONG volatile							m_lFluxOut;

	DWORD volatile							m_dwRemainInLimit;				// �������ƣ���������ͱ��ߵ�
	DWORD volatile							m_dwRemainOutLimit;

	CFBNetwork_T_Dg*						m_pSendDg;

public:
	void		Open(SOCKET Socket, STATE State);
	BOOL		Close(BOOL bForce = true);

	//void		SetState(STATE State);

	//void		PostAcceptEx(void);
	BOOL		AcceptEx(void);
	long const	FluxOut(void){ return InterlockedExchangeAdd(&m_lFluxOut, 0); };


public:
											CFBNetwork_T_Socket();
	virtual									~CFBNetwork_T_Socket();

	STATE									State(void);

	CFBKernel_Vector<CFBNetwork_T_Socket*>*	Accepts(void);

	BOOL									Send(char* pBuffer, DWORD dwLen);
	BOOL									Recv(CFBNetwork_Stuff* pStuff);

	BOOL									End(void);

};