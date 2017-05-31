#include "../include/FBNetwork_Port.h"

void CFBNetwork_Parser_Msg::PadNT(void)
{
	*((char*)((char*)this + m_wSize - 1)) = '\0';
}
void CFBNetwork_Parser_Msg::WPadNT(void)
{
	*((WCHAR*)((char*)this + m_wSize - 2)) = L'\0';
}


void 
CFBNetwork_Parser_Msg::PushStringLess256(
	WCHAR const * const pSrcStr
	, BYTE * const		pData
	, DWORD&			dwPos	
	, DWORD const		dwDesStrLen
	)
{
	BYTE& byLen = pData[ dwPos ];
	dwPos += sizeof( BYTE );

	DWORD dwLen = 0;
	WCHAR* const pDesStr = ((WCHAR*)(&pData[ dwPos ])); 
	if (NULL != pSrcStr)
	{
		dwLen = CFBKernel_String::StrCpy(
			pDesStr
			, pSrcStr
			, dwDesStrLen
			) - 1;

	}
	byLen = static_cast<BYTE>( dwLen );

	dwPos += (byLen * sizeof( WCHAR ));			
}


void 
CFBNetwork_Parser_Msg::PopStringLess256(	
	 BYTE * const		pData
	, DWORD&			dwPos	
	, WCHAR* const		pDesStr
	, DWORD const		dwDesStrLen
	)
{
	DWORD const dwStrLen = (DWORD)__min(pData[ dwPos ], dwDesStrLen - 1);
	dwPos += sizeof( BYTE );

	DWORD const dwCopyLen = sizeof(WCHAR) * dwStrLen;
	CopyMemory(pDesStr, &pData[ dwPos ], dwCopyLen);
	dwPos += dwCopyLen;
	pDesStr[ dwStrLen ] = L'\0';
}


void 
CFBNetwork_Parser_Msg::PushData(	
	void const * const	pData
	, DWORD const		dwDataLen
	, BYTE * const		pBuff
	, DWORD&			dwPos	
	)
{
	memcpy((&pBuff[dwPos]), pData, dwDataLen);
	dwPos += dwDataLen;
}


void 
CFBNetwork_Parser_Msg::PopData(
	BYTE * const		pBuff
	, DWORD&			dwPos
	, void* const		pData
	, DWORD const		dwDataLen
	)
{
	memcpy(pData, (&pBuff[dwPos]), dwDataLen);
	dwPos += dwDataLen;
}



bool const	
CFBNetwork_Parser_Signer::Sign(
	DWORD const		dwMsgType
	, DWORD const	dwMsgMaxSize
	, DWORD const	dwMsgMinSize /*= sizeof( CFBNetwork_Parser_Msg )*/
	)
{
	FBKernel_Assert(dwMsgType <= static_cast<DWORD>( USHRT_MAX ));
	FBKernel_Assert(0 != dwMsgType);

	if (dwMsgType >= m_Msgs.size() || 0 == dwMsgType)
	{
		wcout	<< L"函数["	<< __FUNCTIONW__ << L"]\n"
				<< L"文件["	<< __FILEW__	 << L"]\n"
				<< L"行["	<< __LINE__		 << L"]\n"
				<< L"dwType[" << dwMsgType	 << L"]\n"
				<< L"错误的消息类型"
				<< endl;
		return false;
	}

	FBKernel_Assert(0 == m_Msgs[dwMsgType].first);
	FBKernel_Assert(m_Msgs[dwMsgType].second == 0);
	if (0 != m_Msgs[dwMsgType].first || 0 != m_Msgs[dwMsgType].second)
	{
		wcout	<< L"函数["	<< __FUNCTIONW__ << L"]\n"
				<< L"文件["	<< __FILEW__	 << L"]\n"
				<< L"行["	<< __LINE__		 << L"]\n"
				<< L"dwType[" << dwMsgType	 << L"]\n"
				<< L"消息已注册"
				<< endl;
		return false;
	}

	FBKernel_Assert(dwMsgMaxSize <= static_cast<DWORD>( USHRT_MAX ));
	if (dwMsgMaxSize > static_cast<DWORD>( USHRT_MAX ))
	{
		wcout	<< L"函数["	<< __FUNCTIONW__ << L"]\n"
				<< L"文件["	<< __FILEW__	 << L"]\n"
				<< L"行["	<< __LINE__		 << L"]\n"
				<< L"dwType[" << dwMsgType	 << L"]\n"
				<< L"dwMsgMaxSize=" << dwMsgMaxSize
				<< endl;
		return false;
	}
	FBKernel_Assert(dwMsgMinSize <= dwMsgMaxSize);
	if (dwMsgMinSize > dwMsgMaxSize)
	{
		wcout	<< L"函数["	<< __FUNCTIONW__ << L"]\n"
				<< L"文件["	<< __FILEW__	 << L"]\n"
				<< L"行["	<< __LINE__		 << L"]\n"
				<< L"dwType[" << dwMsgType	 << L"]\n"
				<< L"dwMsgMaxSize=" << dwMsgMaxSize
				<< L"dwMsgMinSize=" << dwMsgMinSize
				<< endl;
		return false;
	}

	m_Msgs[ dwMsgType ].first = dwMsgMinSize;
	m_Msgs[ dwMsgType ].second = dwMsgMaxSize;

	return true;
}



CFBNetwork_Parser::CFBNetwork_Parser( )
: m_dwBuffers( 0 )
, m_dwOffset( 0 )
{
 
}
CFBNetwork_Parser::~CFBNetwork_Parser( )
{
	Release();
}

void CFBNetwork_Parser::Release( void )
{
	m_dwBuffers = 0;
	m_Buffer.Release();
	m_dwOffset = 0;

	m_Msgs.Release();
}


bool const	
CFBNetwork_Parser::Parser(
	CFBNetwork_Stuff*			const pStuff
	, CFBNetwork_Parser_Signer* const pSigner
	, WORD* 					const pErrorType /*= 0*/
	, WORD* 					const pErrorSize /*= 0*/
	)
{
	// 将上次处理缓冲区中无法识别的数据复制到开始处
	if (m_dwOffset > 0)
	{
		CopyMemory(&m_Buffer[0], &m_Buffer[0] + m_dwOffset, m_dwBuffers);
		m_dwOffset = 0;
	}

	// 将接收缓冲区的内容复制到处理缓冲区尾部
	for (DWORD n = 0; n < pStuff->m_Dgs.Size(); ++n)
	{
		// 处理缓冲区扩容
		m_Buffer.Resize(m_dwBuffers + pStuff->m_Dgs[n]->DataLen());

		// 复制
		CopyMemory(&m_Buffer[0] + m_dwBuffers, pStuff->m_Dgs[n]->Data(), pStuff->m_Dgs[n]->DataLen());
		m_dwBuffers += pStuff->m_Dgs[n]->DataLen();
	}

	// 开始分析处理缓冲区中的数据
	m_Msgs.Release();
	while (m_dwBuffers >= static_cast<DWORD>( sizeof( CFBNetwork_Parser_Msg ) ))
	{
		CFBNetwork_Parser_Msg* pMsg = reinterpret_cast<CFBNetwork_Parser_Msg* >(&m_Buffer[0] + m_dwOffset);
		{// 看看这个type的size是否合法
			if (0 == pMsg->m_wType || pMsg->m_wType >= pSigner->m_Msgs.size())
			{// 没有这个消息
				if (NULL != pErrorType)
				{
					*pErrorType = pMsg->m_wType;
				}
				if (NULL != pErrorSize)
				{
					*pErrorSize = pMsg->m_wSize;
				}
				return false;
			}
			else
			{// 检查消息size
				CFBNetwork_Parser_Signer::TypeMap::value_type const& Msg = pSigner->m_Msgs[ pMsg->m_wType ];
				if (pMsg->m_wSize < Msg.first || pMsg->m_wSize > Msg.second)
				{// 消息长度不合法
					if (NULL != pErrorType)
					{
						*pErrorType = pMsg->m_wType;
					}
					if (NULL != pErrorSize)
					{
						*pErrorSize = pMsg->m_wSize;
					}
					return false;
				}
			}
		}

		// 看看是否包含整条消息
		if (m_dwBuffers >= static_cast<DWORD>( pMsg->m_wSize ))
		{
			// 分析出一条消息了
			m_Msgs() = pMsg;

			m_dwBuffers -= pMsg->m_wSize;
			m_dwOffset += pMsg->m_wSize;
		}
		else
		{
			break;
		}
	}

	return true;
}
void		
CFBNetwork_Parser::Break(DWORD dwLastProcessedMsg)
{
	for(DWORD n = dwLastProcessedMsg; n < m_Msgs.Size(); ++n)
	{
		CFBNetwork_Parser_Msg* pMsg = m_Msgs[n];

		m_dwBuffers += pMsg->m_wSize;
		m_dwOffset -= pMsg->m_wSize;
	}
}