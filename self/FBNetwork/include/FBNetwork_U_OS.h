#pragma once

class CFBNetwork_U_Socket;

class CFBNetwork_U_OS_Notify : public CFBKernel_List_Node<CFBNetwork_U_OS_Notify>
{
public:
	CFBNetwork_U_Socket*							m_pSocket;				// 连接
};
class CFBNetwork_U_OS
{
public:
	HANDLE											m_hThread;				// 线程
	HANDLE											m_pEvent[2];			// 事件

	CFBKernel_List<CFBNetwork_U_OS_Notify>			m_Notifys;				// 通知链表,当连接有数据要发送的时候就放到这个链表里

	mutex											m_Mutex;				// 锁

public:
	static DWORD				Thread(CFBNetwork_U_OS* pOS);

public:
	DWORD						Thread_Process(void);

public:
	void						Init(CFBNetwork_U* pU);
	void						Quit(void);
	
	void						Push(CFBNetwork_U_OS_Notify* pNotify);
	void						Pop(CFBNetwork_U_OS_Notify* pNotify);
	CFBNetwork_U_OS_Notify*		Get(void);
};
