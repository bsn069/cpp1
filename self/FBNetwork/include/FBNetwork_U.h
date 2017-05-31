#pragma once

class FBNETWORK_API CFBNetwork_U
{
public:
	typedef 	hash_map<
		DWORD, 
		CFBNetwork_U_Socket*,
		hash_compare<DWORD, less<DWORD>>,
		pool_allocator<pair<DWORD, CFBNetwork_U_Socket*>>> 
		IDMap;

	typedef 	hash_map<
		__int64, 
		IDMap*,
		hash_compare<__int64, less<__int64>>,
		pool_allocator<pair<__int64, IDMap*>>> 
		AddrMap;

public: 
	enum IDTYPE
	{
		IDT_P2P = 0,
		IDT_CS,
	};

public:
	SOCKET													m_Socket;				// Socket

	BOOL volatile											m_bListen;				// �Ƿ��ڼ���״̬

	BOOL volatile											m_bQuit;				// ���߳��˳���־
	HANDLE													m_hThread;				// ���߳�

	CFBNetwork_U_IS											m_IS;					// ������
	CFBNetwork_U_OS											m_OS;					// �����

	AddrMap													m_AddrMap;				// IPPortΪKey��has_map,�������IDΪKey������
	CFBKernel_List<CFBNetwork_U_Socket>						m_Sockets;				// ��������
	shared_mutex											m_SocketMutex;			// ������

	CFBKernel_List<CFBNetwork_U_Socket>						m_DSockets;				// �Ѿ�����������

	CFBKernel_Double<CFBNetwork_U_Socket*>					m_Accepts;				// �½��ܵ�����

public:
	static								DWORD Thread(CFBNetwork_U* pU);

public:
	DWORD								Thread_Process(void);
	
	DWORD								ID(sockaddr_in* pAddr);
	IDTYPE								IDType(DWORD dwID);

	void								PushSocket(CFBNetwork_U_Socket* pSocket);
	CFBNetwork_U_Socket*				PopSocket(CFBNetwork_U_Socket* pSocket);
	CFBNetwork_U_Socket*				QuerySocket(sockaddr_in* pAddr, DWORD dwID, BOOL bUsedByIS);
	CFBNetwork_U_Socket*				GetSocket(CFBNetwork_U_Socket* pSocket);

public:
	static DWORD						SwapID(DWORD dwID);

public:
										CFBNetwork_U();
	virtual								~CFBNetwork_U();

	BOOL								Init(sockaddr_in* pAddr);
	void								Quit(void);

	void									Listen(BOOL bTrue);
	CFBKernel_Vector<CFBNetwork_U_Socket*>*	Accepts(void);

	CFBNetwork_U_Socket*				Connect(sockaddr_in* pAddr, char* pData, DWORD dwDatas, DWORD dwID, BOOL bBlock);
	void								Close(CFBNetwork_U_Socket* pSocket);
};
