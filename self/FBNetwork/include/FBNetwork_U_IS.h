#pragma once

class CFBNetwork_U;

class CFBNetwork_U_IS
{
public:
	BOOL volatile									m_bQuit;			// �˳���־
	HANDLE											m_hThread;			// �߳�

	CFBNetwork_U*									m_pU;				//

public:
	static DWORD				Thread(CFBNetwork_U_IS* pIS);

public:
	void						Init(CFBNetwork_U* pU);
	void						Quit(void);
};