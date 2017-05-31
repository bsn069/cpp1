#pragma once

class FBNETWORK_API CFBNetwork_Stuff
{
public:
	CFBKernel_Vector<CFBNetwork_Dg*>				m_Dgs;			// 接收到的数据报

	DWORD											m_dwBytes;		// 接收到多少个字节

public:
	void										Push(CFBNetwork_Dg* pDg);

public:
												CFBNetwork_Stuff();
	virtual										~CFBNetwork_Stuff();

	void										Release(void);
};