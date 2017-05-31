#include "../include/FBNetwork_Port.h"

CFBNetwork_Stuff::CFBNetwork_Stuff()
{
	m_dwBytes = 0;
}
CFBNetwork_Stuff::~CFBNetwork_Stuff()
{
	Release();
}

void CFBNetwork_Stuff::Release(void)
{
	for(DWORD n = 0; n < m_Dgs.Size(); n++)
	{
		FB_DELETE(m_Dgs[n]);
	}
	m_Dgs.Release();

	m_dwBytes = 0;
}

void CFBNetwork_Stuff::Push(CFBNetwork_Dg* pDg)
{
	m_Dgs() = pDg;

	m_dwBytes += pDg->DataLen();
}
