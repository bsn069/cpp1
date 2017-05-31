#pragma once

class CFBNetwork_U_Socket;

class CFBNetwork_U_OS_Notify : public CFBKernel_List_Node<CFBNetwork_U_OS_Notify>
{
public:
	CFBNetwork_U_Socket*							m_pSocket;				// ����
};
class CFBNetwork_U_OS
{
public:
	HANDLE											m_hThread;				// �߳�
	HANDLE											m_pEvent[2];			// �¼�

	CFBKernel_List<CFBNetwork_U_OS_Notify>			m_Notifys;				// ֪ͨ����,������������Ҫ���͵�ʱ��ͷŵ����������

	mutex											m_Mutex;				// ��

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
