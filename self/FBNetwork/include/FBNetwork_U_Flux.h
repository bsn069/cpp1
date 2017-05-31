#pragma once

class CFBNetwork_U_Flux_Notify
{
public:
	HANDLE										m_hEvent;
	DWORD										m_dwBytes;

public:
	CFBNetwork_U_Flux_Notify();
	virtual ~CFBNetwork_U_Flux_Notify();
};

class CFBNetwork_U_Flux
{
public:
	typedef 	hash_map<
		DWORD, 
		CFBNetwork_U_Flux_Notify*, 
		hash_compare<DWORD, less<DWORD>>,
		pool_allocator<pair<DWORD, CFBNetwork_U_Flux_Notify*>>>
		ThreadMap;

public:
	BOOL volatile													m_bBreak;			// 是否打断所有阻塞的写操作

	DWORD															m_dwSWnd;			// 最大发送缓冲
	DWORD															m_dwSWndNow;		// 当前发送缓冲

	DWORD															m_dwRWnd;			// 对方滑动窗口
	DWORD															m_dwRWndNow;		// 当前滑动窗口

	DWORD															m_dwCWnd;			// 拥塞窗口
	DWORD															m_dwCWndSsthresh;	// 拥塞窗口门限

	CFBKernel_Timer													m_CWndTimer;		// 拥塞窗口计时器
	double															m_dCWndTimerLast;	// 上一次调整拥塞窗口的时间

	ThreadMap														m_Notifys;			// 每个线程的阻塞通知

	mutex															m_Mutex;			// 锁

	//FILE*															m_pFile;			

	//CFBKernel_Double<wstring>										m_Debug;			// 调试信息

public:
									CFBNetwork_U_Flux();
	virtual							~CFBNetwork_U_Flux();

	CFBNetwork_U_Flux_Notify*		CheckIn(DWORD dwBytes, BOOL bBlock);

	BOOL							CanFlow(DWORD dwBytes);
	BOOL							Flow(DWORD dwBytes);
	
	void							Update(DWORD dwBytes, DWORD dwRWnd);

	void							Wait(CFBNetwork_U_Flux_Notify* pNotify);
	void							Break(void);

	void							OnACK(void);
	void							OnLost(void);
	void							OnTimeout(void);
};