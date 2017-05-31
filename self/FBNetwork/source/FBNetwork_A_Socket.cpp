#include "../include/FBNetwork_Port.h"

void CFBNetwork_A_Socket::Read(void)
{
	CFBNetwork_A_Dg* pDg = FB_NEW(CFBNetwork_A_Dg, 1);
	async_read(
		m_Socket, 
		buffer(pDg->m_pBuffer, CFBNetwork_A_Dg::BUF_SIZE), 
		transfer_at_least(1),
		bind(&CFBNetwork_A_Socket::OnRead, shared_from_this(), pDg, placeholders::error, placeholders::bytes_transferred));
}

void CFBNetwork_A_Socket::OnRead(CFBNetwork_A_Dg* pDg, const error_code &Error, size_t Bytes)
{
	if(Error)
	{
		FB_DELETE(pDg);

		InterlockedExchange((LONG volatile*)&m_State, S_CLOSE);
		return;
	}

	//
	pDg->m_dwLen = (DWORD)Bytes;
	m_Dgs.Push(pDg);

	// 发出一个异步读取
	Read();
}
void CFBNetwork_A_Socket::OnWrite(CFBNetwork_A_Dg* pDg, const error_code& Error, size_t Bytes)
{
	InterlockedExchangeAdd(&m_lFluxOut, -(LONG)Bytes);

	FB_DELETE(pDg);

	if(Error)
	{
		InterlockedExchange((LONG volatile*)&m_State, S_CLOSE);
		return;
	}
}

CFBNetwork_A_Socket::CFBNetwork_A_Socket(CFBNetwork_A* pA) : m_Socket(pA->m_IO)
{
	#ifdef _DEBUG
	m_pTemp = FB_NEW(char, 1);
	#endif

	m_pSendDg = 0;

	InterlockedExchange(&m_lFluxOut, 0);
}
CFBNetwork_A_Socket::~CFBNetwork_A_Socket()
{
	#ifdef _DEBUG
	FB_DELETE(m_pTemp);
	#endif
}

BOOL CFBNetwork_A_Socket::Send(char* pBuffer, DWORD dwLen)
{
	// 将消息复制到当前over 
	DWORD dwCopyed = 0;
	while(1)
	{
		if(!m_pSendDg)
		{
			m_pSendDg = FB_NEW(CFBNetwork_A_Dg, 1);
		}

		DWORD dwBytes = __min(CFBNetwork_A_Dg::BUF_SIZE - m_pSendDg->m_dwLen, dwLen - dwCopyed);
		CopyMemory(
			m_pSendDg->m_pBuffer + m_pSendDg->m_dwLen,
			pBuffer + dwCopyed, 
			dwBytes);

		m_pSendDg->m_dwLen += dwBytes;
		dwCopyed += dwBytes;

		if(m_pSendDg->m_dwLen == CFBNetwork_A_Dg::BUF_SIZE)
		{
			if(!End())
			{
				return false;
			}
		}

		if(dwCopyed == dwLen)
		{
			break;
		}
	}
	return true;
}
BOOL CFBNetwork_A_Socket::Recv(CFBNetwork_Stuff* pStuff)
{
	pStuff->Release();

	// 计算总共接收了多少个字节
	CFBKernel_Vector<CFBNetwork_A_Dg*>* pVector = m_Dgs.Flip();
	for(DWORD n = 0; n < pVector->Size(); n++)
	{
		pStuff->Push((*pVector)[n]);
	}

	return true;
}

BOOL CFBNetwork_A_Socket::End(void)
{
	if(m_pSendDg)
	{
		InterlockedExchangeAdd(&m_lFluxOut, (LONG)m_pSendDg->m_dwLen);

		// 发送over
		async_write(
			m_Socket, 
			buffer(m_pSendDg->m_pBuffer, m_pSendDg->m_dwLen),
			bind(&CFBNetwork_A_Socket::OnWrite, shared_from_this(), m_pSendDg, placeholders::error, placeholders::bytes_transferred));

		m_pSendDg = 0;
	}

	return true;
}

CFBNetwork_A_Socket::STATE CFBNetwork_A_Socket::State(void)
{
	return (STATE)InterlockedExchangeAdd((LONG volatile*)&m_State, 0);
}


