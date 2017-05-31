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

	BOOL volatile											m_bListen;				// 是否处于监听状态

	BOOL volatile											m_bQuit;				// 主线程退出标志
	HANDLE													m_hThread;				// 主线程

	CFBNetwork_U_IS											m_IS;					// 输入流
	CFBNetwork_U_OS											m_OS;					// 输出流

	AddrMap													m_AddrMap;				// IPPort为Key的has_map,里面存着ID为Key的连接
	CFBKernel_List<CFBNetwork_U_Socket>						m_Sockets;				// 连接链表
	shared_mutex											m_SocketMutex;			// 连接锁

	CFBKernel_List<CFBNetwork_U_Socket>						m_DSockets;				// 已经抛弃的连接

	CFBKernel_Double<CFBNetwork_U_Socket*>					m_Accepts;				// 新接受的连接

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
