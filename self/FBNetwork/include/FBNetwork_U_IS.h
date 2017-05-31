#pragma once

class CFBNetwork_U;

class CFBNetwork_U_IS
{
public:
	BOOL volatile									m_bQuit;			// 退出标志
	HANDLE											m_hThread;			// 线程

	CFBNetwork_U*									m_pU;				//

public:
	static DWORD				Thread(CFBNetwork_U_IS* pIS);

public:
	void						Init(CFBNetwork_U* pU);
	void						Quit(void);
};