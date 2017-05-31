#pragma once

#pragma pack(1)
/*
// ��Ϣ���� �������麯��
class CFZLCommon_Msg_XXX : public CFBNetwork_Parser_Msg
{
public:// ÿ����Ϣ������
	enum
	{
		// ��Ϣ���� FZLCommon_MsgIndex.h
		TYPE		= EMI***,
		// ��Ϣ����С����
		MIN_SIZE	= ( // ����һ��
		sizeof( CFBNetwork_Parser_Msg ) 
		+ ...
		),// ����һ��
	};


public:// ���ݶ���
	// �����ַ������� ����Ҫ+1 ������0
	// boolֵ��BYTE��ʾ
	// �䳤���ݷ������


public:
	CFZLCommon_Msg_XXX( )
	{
		m_wType = TYPE;

		// �������Ϳ��Է��͵���Ϣ д�����캯����
		m_wSize = sizeof( *this ); 
	}

	// �����������ַ��� ��������ĺ��� �������ַ���ĩβ��0
	void Pad( void )
	{
		// �����һ����Ա���ַ��� ��ֱ�ӵ��ö�Ӧ����
		PadNT(); // ������char�ַ���
		WPadNT();// ������w_char�ַ���
	}

	// ������Ϣ���
	void Fill( ... )
	{
		// ���ſ��Է��͵Ķ�����Ϣ ��ֹδ���ͷ��� д����亯����
		m_wSize = sizeof( *this ); 
	}

	// �䳤��Ϣ���
	void Fill_P( ... )
	{
		DWORD const dwLen = CFBKernel_String::StrCpy(m_pPlayerName, pName, FZL_ArraySize(m_pPlayerName));

		// ���ſ��Է��͵ı䳤��Ϣ ��ֹδ���ͷ���
		m_wSize = GetSize();
	}
	
	bool const 	CheckSize( void ) const
	{// cl�����ı߳���Ϣ ������������
		return (GetSize() == m_wSize);
	}

	private:
	WORD const 	GetSize( void ) const
	{
		return static_cast<WORD>(
			+ sizeof( CFBNetwork_Parser_Msg ) // �����д���
			+ sizeof( ������ ) // ��ͨ������
			+ sizeof( array[ 0 ] ) * arraysize // �䳤������
			); 
	}
};
//*/

/*
// �������Ϳ��Է��͵���Ϣ 
CFZLCommon_Msg_1 Msg_1;
Send( &Msg_1 );

// ���ſ��Է��͵Ķ�����Ϣ ��ֹδ���ͷ���
CFZLCommon_Msg_2 Msg_2;
Msg_2.Fill( 3 );
Send( &Msg_2 );

// ���ſ��Է��͵ı䳤��Ϣ  
CFZLCommon_Msg_3 Msg_3;
Msg_2.Fill_P( 5 );
Send( &Msg_3 );
//*/


/* ѹ����Ϣ��ʽ
CFZLCommon_Msg_G2C_Faction_FightHistory

class CFZLCommon_Msg_G2C_SongHua_2All_CL
{
public:
// SongHua::E_HuaType
BYTE	m_byHuaType;
WCHAR	m_pPlayerName_SongHua[Player::msc_dwNameShowMax + 1];
WCHAR	m_pPlayerName_ShouHua[Player::msc_dwNameShowMax + 1];

void Init( void )
{
m_byHuaType = static_cast<BYTE>( SongHua::EHTs );
m_pPlayerName_SongHua[ 0 ] = L'\0';
m_pPlayerName_ShouHua[ 0 ] = L'\0';
}
};
class CFZLCommon_Msg_G2C_SongHua_2All : public CFBNetwork_Parser_Msg
{
public:
enum
{
TYPE	= EMIG2C_CFZLCommon_Msg_G2C_SongHua_2All,

MIN_SIZE = (
sizeof( CFBNetwork_Parser_Msg )
+ sizeof( BYTE )
),
};


public:
void Set(CFZLCommon_Msg_G2C_SongHua_2All_CL* const pCLData)
{
FBKernel_Assert(NULL != pCLData);

pCLData->Init();
pCLData->m_byHuaType = m_byHuaType;

DWORD dwPos = 0;
PopStringLess256(
m_byBuff
, dwPos
, pCLData->m_pPlayerName_SongHua
, FZL_ArraySize( pCLData->m_pPlayerName_SongHua )
);
PopStringLess256(
m_byBuff
, dwPos
, pCLData->m_pPlayerName_ShouHua
, FZL_ArraySize( pCLData->m_pPlayerName_ShouHua )
);
}


void Fill_P(
BYTE const byHuaType
, WCHAR const * const pPlayerName_SongHua
, WCHAR const * const pPlayerName_ShouHua
)
{
FBKernel_Assert(NULL != pPlayerName_ShouHua);
FBKernel_Assert(NULL != pPlayerName_ShouHua);

m_byHuaType = byHuaType;

DWORD dwPos = 0;
PushStringLess256(
pPlayerName_SongHua
, m_byBuff
, dwPos
, CFZLCommon_Msg_G2C_SongHua_2All_CL::m_pPlayerName_SongHua
);
PushStringLess256(
pPlayerName_ShouHua
, m_byBuff
, dwPos
, CFZLCommon_Msg_G2C_SongHua_2All_CL::m_pPlayerName_ShouHua
);

m_wSize = static_cast<WORD>(
sizeof( CFBNetwork_Parser_Msg )
+ sizeof( m_byHuaType )
+ dwPos
);
}


public:
// SongHua::E_HuaType
BYTE	m_byHuaType;
BYTE	m_byBuff[(CFZLCommon_Player::msc_dwNameMax + 1) * 2];


public:
CFZLCommon_Msg_G2C_SongHua_2All( )
{
m_wType = TYPE;
}
};
 */

class FBNETWORK_API CFBNetwork_Parser_Msg
{
public:
	// ����
	WORD	m_wType;	
	// ���ȣ�����������Ϣ��   
	WORD	m_wSize;		

public:
	// Ϊ���һ���ַ�����Ա�����ַ���������
	void	PadNT( void );
	void	WPadNT( void );

	// ������<256���ַ������л�
	void	PushStringLess256(
				WCHAR const * const pSrcStr
				, BYTE * const		pData
				, DWORD&			dwPos	
				, DWORD const		dwDesStrLen
				);
	void	PopStringLess256(
				 BYTE * const		pData
				, DWORD&			dwPos	
				, WCHAR* const		pDesStr
				, DWORD const		dwDesStrLen
				);
	// ���л�����
	void	PushData(	
				void const * const	pData
				, DWORD const		dwDataLen
				, BYTE * const		pBuff
				, DWORD&			dwPos	
				);
	void	PopData(				
				BYTE * const		pBuff
				, DWORD&			dwPos
				, void* const		pData
				, DWORD const		dwDataLen
				);
	// ��ȡָ��λ�õ�ָ��
	template<typename T_ValueType>
	T_ValueType* const	GetValuePtr(
							BYTE const * const		pData
							, DWORD&			dwPos		
							);
	// ����ֵ���л�
	template<typename T_ValueType>
	void 	PushValue(
				T_ValueType const&	Value
				, BYTE * const		pData
				, DWORD&			dwPos		
				);
	template<typename T_ValueType>
	void 	PopValue(
				BYTE const * const		pData
				, DWORD&			dwPos	
				, T_ValueType&		Value
				);

public:
	CFBNetwork_Parser_Msg( )
		: m_wSize( 0 )
	{ 
	};
};


template<typename T_ValueType>
T_ValueType* const
CFBNetwork_Parser_Msg::GetValuePtr(
	BYTE const * const		pData
	 , DWORD&			dwPos		
	 )
{
	T_ValueType* const pValue = ((T_ValueType* const)(&pData[dwPos]));
	dwPos += sizeof( T_ValueType );
	return pValue;
}


template<typename T_ValueType>
void 
CFBNetwork_Parser_Msg::PushValue(
	T_ValueType const&	Value
	, BYTE * const		pData
	, DWORD&			dwPos		
	)
{
	*(GetValuePtr<T_ValueType>(pData, dwPos)) = Value;
}


template<typename T_ValueType>
void 
CFBNetwork_Parser_Msg::PopValue(
	BYTE const * const		pData
	, DWORD&			dwPos	
	, T_ValueType&		Value
	)
{
	Value = *(GetValuePtr<T_ValueType>(pData, dwPos));
}
#pragma pack()


class FBNETWORK_API CFBNetwork_Parser_Signer
{
public:
	// <��Ϣ����, <��Ϣ��Сsize�� ��Ϣ���size>>
	typedef vector< pair<DWORD, DWORD> > TypeMap;


public:
	// ����ע�����Ϣ
	TypeMap	m_Msgs;	


public:
	// ��Ϣ����dwType 
	bool const	Sign(
					DWORD const		dwMsgType
					, DWORD const	dwMsgMaxSize
					, DWORD const	dwMsgMinSize = sizeof( CFBNetwork_Parser_Msg )
					);
	// ע����ϢMSG_TYPE
	template<typename MSG_TYPE>
	bool const	Sign( void );

	void Init(DWORD const dwMsgIndexMax)
	{
		m_Msgs.resize(dwMsgIndexMax + 1, make_pair(0, 0));
	}
};


class FBNETWORK_API CFBNetwork_Parser
{
public:
	void		Release( void );

	bool const	Parser(
					CFBNetwork_Stuff*			const pStuff
					, CFBNetwork_Parser_Signer* const pSigner
					, WORD* 					const pErrorType = 0
					, WORD* 					const pErrorSize = 0
					);
	/*
	��ʱ����ĳ����Ϣ֮���Ҫ���������̣���ͣ�������Ϣ����Ȼ���������������ڼ���������Ϣ����Ҫ�õ��������
	*/
	void		Break(DWORD dwLastProcessedMsg);

public:
	DWORD										m_dwBuffers;	// ����������С
	CFBKernel_Vector<char>						m_Buffer;		// ��������
	DWORD										m_dwOffset;		// ����������ʼλ��

	CFBKernel_Vector<CFBNetwork_Parser_Msg* >	m_Msgs;			// ������������Ϣ


public:
				CFBNetwork_Parser( );
				~CFBNetwork_Parser( );
};



template<typename MSG_TYPE>
bool const
CFBNetwork_Parser_Signer::Sign( void )
{
	BOOST_STATIC_ASSERT(static_cast<DWORD>( MSG_TYPE::TYPE ) <= static_cast<DWORD>( USHRT_MAX ));
	// ��ֹ��Ϣ������С��ʾ
	BOOST_STATIC_ASSERT(static_cast<DWORD>( sizeof( MSG_TYPE ) ) <= static_cast<DWORD>( USHRT_MAX ));
	BOOST_STATIC_ASSERT(static_cast<DWORD>( MSG_TYPE::MIN_SIZE ) <= static_cast<DWORD>( sizeof( MSG_TYPE ) ));
	BOOST_STATIC_ASSERT(static_cast<DWORD>( MSG_TYPE::MIN_SIZE ) >= static_cast<DWORD>( sizeof( CFBNetwork_Parser_Msg ) ));

	DWORD const dwType	= static_cast<DWORD>( MSG_TYPE::TYPE );
	DWORD const dwMaxSize = static_cast<DWORD>( sizeof( MSG_TYPE ) );
	DWORD const dwMinSize = static_cast<DWORD>( MSG_TYPE::MIN_SIZE );

	return Sign(dwType, dwMaxSize, dwMinSize);
}
