#pragma once

class CFBNetwork_U;

class FBNETWORK_API CFBNetwork_U_Socket : public CFBKernel_List_Node<CFBNetwork_U_Socket>
{
public:
	typedef		hash_map<
		DWORD, 
		CFBNetwork_U_Dg*, 
		hash_compare<DWORD, less<DWORD>>,
		pool_allocator<pair<DWORD, CFBNetwork_U_Dg*>>>
		SEQMap;

public:
	enum
	{
		DELAYACKS											= 3,
	};

	enum STATE
	{
		S_CLOSE												= 0,
		S_CONNECTING,
		S_ESTABLISHED,
	};

public:
	CFBNetwork_U*											m_pU;					// 

	DWORD													m_dwID;					// ����ID

	STATE volatile											m_State;				// ״̬

	sockaddr_in												m_RAddr;				// Զ�̵�ַ

	CFBKernel_Vector<char>									m_LData;				// �������Ӹ�������
	DWORD													m_dwLDatas;				// �������Ӹ������ݳ���

	CFBKernel_Vector<char>									m_RData;				// Զ�����Ӹ�������
	DWORD													m_dwRDatas;				// Զ�����Ӹ������ݳ���

	double													m_dConnectTimer;		// ���Ӽ�ʱ��
	DWORD													m_dwConnectTimes;		// ���Ӵ���

	HANDLE													m_hConnectEvent;		// ��������֪ͨ�¼�

	BOOL volatile											m_bDiscarded;			// �û��Ƿ�����˶����Socket�Ĳ���
	BOOL volatile											m_bUsedByIS;			// IS�Ƿ�����ʹ�����Socket

	CFBNetwork_U_OS_Notify									m_OSNotify;				// ��OS��֪ͨ

	CFBNetwork_U_Flux										m_Flux;					// ��������

	DWORD volatile											m_dwSEQ;				// ������һ��Dgʹ�õ����
	DWORD volatile											m_dwWanted;				// ��Ҫ���յ����

	DWORD													m_dwLastACK;			// ���һ���յ���ACK
	DWORD													m_dwLastACKs;			// ���һ���յ�ͬ����ACK����

	CFBKernel_List<CFBNetwork_U_Dg>							m_SDgs;					// ��Ҫ���͵�Dg
	mutex													m_SDgMutex;				// ��Ҫ���͵�Dg��

	CFBKernel_List<CFBNetwork_U_Dg>							m_BDgs;					// �Ѿ����͵�Dg
	mutex													m_BDgMutex;				// �Ѿ����͵�Dg��

	SEQMap													m_RDgs;					// ���յ���Dg

	CFBKernel_Double<CFBNetwork_U_Dg*>						m_FDgs;					// ���Թ��ϲ��ȡ��Dg

	DWORD													m_dwRBuffer;			// �����ջ���
	DWORD volatile											m_dwRBufferNow;			// ��ǰ���ջ���

	mutex													m_RMutex;				// ������
	DWORD													m_RBytes;				// �����˶����ֽ�,��������ֽ���������һ��������Ҫ������֪ͨ��
																					// �������������Ϳ�����ۺ�֢����

	double													m_dWndTimer;			// ���ʹ���֪ͨ��ʱ��
	DWORD volatile											m_dwAliveTimer;			// ����ʱ��

	DWORD													m_dwDelayACKs;			// �ӳٷ��͵�ACK��

public:
	void									Init(sockaddr_in* pAddr, DWORD dwID, CFBNetwork_U* pU);

	void									SetState(STATE State);

	void									SetUsedByIS(BOOL bTrue);

	void									NotifyOS(void);

	void									SendTo(CFBNetwork_U_Dg* pDg);

	void									OnAlive(void);
	void									OnSEQ(CFBNetwork_U_Dg* pDg);
	void									OnACK(CFBNetwork_U_Dg* pDg);
	void									OnWnd(CFBNetwork_U_Dg* pDg);

	void									OnTimer_Connecting(double dElapsed);
	void									OnTimer_Established(double dElapsed);

public:
	virtual									~CFBNetwork_U_Socket();

	STATE									State(void);
	sockaddr_in*							RAddr(void);
	pair<char*, DWORD>						RData(void);

	BOOL									Send(char* pBuffer, DWORD dwLen, BOOL bBlock);
	BOOL									Recv(CFBNetwork_Stuff* pStuff, BOOL bBlock);
};