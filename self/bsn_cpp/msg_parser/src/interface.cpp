#include "./interface.h"
D_BsnNamespace1(MsgParser)
//////////////////////////////////////////////////////////////////////

T_wchar D_const * D_const C_Interface::Error(T_int32 D_const i32ErrorCode) D_const
{
	switch (i32ErrorCode)
	{
		case 1: return L"1";
		case 2: return L"must > 0";
		default: return L"Unknown";
	}
}


T_wchar D_const * D_const  C_Interface::Name() D_const
{
	return L"C_Imp";
}


C_Interface::C_Interface()
: m_u32Offset(0)
, m_u32Len(0)
, m_u32BufferSize(msc_incSize)
, m_u32IncSize( 512 )
{
	m_pBuffer = Malloc<T_byte>(m_u32BufferSize);
}


C_Interface::~C_Interface()
{
	Free(m_pBuffer);
}


T_int32 D_const
C_Interface::Push(T_Buffers D_const * D_const pBuffers)
{
	if (!m_Msgs.empty())
	{
		m_Msgs.clear();
	}
	D_Assert(!pBuffers->empty());

	if (m_u32Len > 0)
	{// 上次未处理的 移动到开始位置
		CopyMemory(m_pBuffer, m_pBuffer + m_u32Offset, m_u32Len);
	}
	m_u32Offset = m_u32Len;

	for (auto i : *pBuffers)
	{
		m_u32Len += i->Len();
	}

	if (m_u32Len > m_u32BufferSize)
	{// 扩容 msc_incSize 倍数
		m_u32BufferSize = ((m_u32Len / m_u32IncSize) + 1) * m_u32IncSize;
		realloc((T_void*)m_pBuffer, m_u32BufferSize);
	}

	for (auto i : *pBuffers)
	{// 将所有数据放到处理缓冲区
		CopyMemory(m_pBuffer + m_u32Offset, i->Data(), i->Len());
		m_u32Offset += i->Len();
	}

	m_u32Offset = 0;
	T_MsgHeader* pMsg = T_nullptr;
	while (m_u32Len >= sizeof(T_MsgHeader))
	{// 够消息头
		pMsg = reinterpret_cast<T_MsgHeader*>(m_pBuffer);
		if (m_u32Len < pMsg->m_Len)
		{// 缓冲区不够一个消息
			break;
		}

		m_Msgs.push_back(pMsg);
		m_u32Offset += pMsg->m_Len;
		m_u32Len -= pMsg->m_Len;
	}

	return 0;
}


T_int32 D_const
C_Interface::Msgs(T_Msgs D_const*& pMsgs) D_const
{
	pMsgs = &m_Msgs;
	return 0;
}


T_int32 D_const
C_Interface::IncSize(T_uint32 D_const u32IncSize)
{
	if (u32IncSize < 1)
	{
		return 2;
	}
	m_u32IncSize = u32IncSize;
	return 0;
}





//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
