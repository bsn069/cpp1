#pragma once

class FBNETWORK_API CFBNetwork_Stuff
{
public:
	CFBKernel_Vector<CFBNetwork_Dg*>				m_Dgs;			// ���յ������ݱ�

	DWORD											m_dwBytes;		// ���յ����ٸ��ֽ�

public:
	void										Push(CFBNetwork_Dg* pDg);

public:
												CFBNetwork_Stuff();
	virtual										~CFBNetwork_Stuff();

	void										Release(void);
};