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
	BOOL volatile													m_bBreak;			// �Ƿ�������������д����

	DWORD															m_dwSWnd;			// ����ͻ���
	DWORD															m_dwSWndNow;		// ��ǰ���ͻ���

	DWORD															m_dwRWnd;			// �Է���������
	DWORD															m_dwRWndNow;		// ��ǰ��������

	DWORD															m_dwCWnd;			// ӵ������
	DWORD															m_dwCWndSsthresh;	// ӵ����������

	CFBKernel_Timer													m_CWndTimer;		// ӵ�����ڼ�ʱ��
	double															m_dCWndTimerLast;	// ��һ�ε���ӵ�����ڵ�ʱ��

	ThreadMap														m_Notifys;			// ÿ���̵߳�����֪ͨ

	mutex															m_Mutex;			// ��

	//FILE*															m_pFile;			

	//CFBKernel_Double<wstring>										m_Debug;			// ������Ϣ

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