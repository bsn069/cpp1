#pragma once

class FBNETWORK_API CFBNetwork_A_Dg : public CFBNetwork_Dg
{
public:
	enum
	{
		BUF_SIZE		= 2048,
	};

public:
	DWORD								m_dwLen;
	char								m_pBuffer[BUF_SIZE];

public:
										CFBNetwork_A_Dg()
	{
		m_dwLen = 0;
	}
	virtual								~CFBNetwork_A_Dg()
	{
	}

	virtual	DWORD						DataLen(void)
	{
		return m_dwLen;
	}
	virtual char*						Data(void)
	{
		return m_pBuffer;
	}
};