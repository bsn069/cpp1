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

	DWORD													m_dwID;					// 链接ID

	STATE volatile											m_State;				// 状态

	sockaddr_in												m_RAddr;				// 远程地址

	CFBKernel_Vector<char>									m_LData;				// 本地连接附带数据
	DWORD													m_dwLDatas;				// 本地连接附带数据长度

	CFBKernel_Vector<char>									m_RData;				// 远程连接附带数据
	DWORD													m_dwRDatas;				// 远程连接附带数据长度

	double													m_dConnectTimer;		// 连接计时器
	DWORD													m_dwConnectTimes;		// 连接次数

	HANDLE													m_hConnectEvent;		// 阻塞连接通知事件

	BOOL volatile											m_bDiscarded;			// 用户是否放弃了对这个Socket的操作
	BOOL volatile											m_bUsedByIS;			// IS是否正在使用这个Socket

	CFBNetwork_U_OS_Notify									m_OSNotify;				// 给OS的通知

	CFBNetwork_U_Flux										m_Flux;					// 流量控制

	DWORD volatile											m_dwSEQ;				// 发送下一个Dg使用的序号
	DWORD volatile											m_dwWanted;				// 想要接收的序号

	DWORD													m_dwLastACK;			// 最后一次收到的ACK
	DWORD													m_dwLastACKs;			// 最后一次收到同样的ACK次数

	CFBKernel_List<CFBNetwork_U_Dg>							m_SDgs;					// 将要发送的Dg
	mutex													m_SDgMutex;				// 将要发送的Dg锁

	CFBKernel_List<CFBNetwork_U_Dg>							m_BDgs;					// 已经发送的Dg
	mutex													m_BDgMutex;				// 已经发送的Dg锁

	SEQMap													m_RDgs;					// 接收到的Dg

	CFBKernel_Double<CFBNetwork_U_Dg*>						m_FDgs;					// 可以供上层读取的Dg

	DWORD													m_dwRBuffer;			// 最大接收缓冲
	DWORD volatile											m_dwRBufferNow;			// 当前接收缓冲

	mutex													m_RMutex;				// 接收锁
	DWORD													m_RBytes;				// 接收了多少字节,如果接收字节数超过了一定数量就要发窗口通知了
																					// 这是用来避免糊涂窗口综合症问题

	double													m_dWndTimer;			// 发送窗口通知计时器
	DWORD volatile											m_dwAliveTimer;			// 存活计时器

	DWORD													m_dwDelayACKs;			// 延迟发送的ACK数

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