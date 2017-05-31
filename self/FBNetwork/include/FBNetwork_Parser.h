#pragma once

#pragma pack(1)
/*
// 消息定义 不能有虚函数
class CFZLCommon_Msg_XXX : public CFBNetwork_Parser_Msg
{
public:// 每个消息必须有
	enum
	{
		// 消息类型 FZLCommon_MsgIndex.h
		TYPE		= EMI***,
		// 消息的最小长度
		MIN_SIZE	= ( // 单起一行
		sizeof( CFBNetwork_Parser_Msg ) 
		+ ...
		),// 单起一行
	};


public:// 数据定义
	// 所有字符串数据 长度要+1 用作补0
	// bool值用BYTE表示
	// 变长数据放在最后


public:
	CFZLCommon_Msg_XXX( )
	{
		m_wType = TYPE;

		// 不用填充就可以发送的消息 写到构造函数里
		m_wSize = sizeof( *this ); 
	}

	// 若数据中有字符串 加入下面的函数 给所有字符串末尾补0
	void Pad( void )
	{
		// 若最后一个成员是字符串 则直接调用对应函数
		PadNT(); // 最后的是char字符串
		WPadNT();// 最后的是w_char字符串
	}

	// 定长消息填充
	void Fill( ... )
	{
		// 填充才可以发送的定长消息 防止未填充就发送 写到填充函数里
		m_wSize = sizeof( *this ); 
	}

	// 变长消息填充
	void Fill_P( ... )
	{
		DWORD const dwLen = CFBKernel_String::StrCpy(m_pPlayerName, pName, FZL_ArraySize(m_pPlayerName));

		// 填充才可以发送的变长消息 防止未填充就发送
		m_wSize = GetSize();
	}
	
	bool const 	CheckSize( void ) const
	{// cl发来的边长消息 服务器必须检测
		return (GetSize() == m_wSize);
	}

	private:
	WORD const 	GetSize( void ) const
	{
		return static_cast<WORD>(
			+ sizeof( CFBNetwork_Parser_Msg ) // 必须有此行
			+ sizeof( 变量名 ) // 普通变量用
			+ sizeof( array[ 0 ] ) * arraysize // 变长数组用
			); 
	}
};
//*/

/*
// 不用填充就可以发送的消息 
CFZLCommon_Msg_1 Msg_1;
Send( &Msg_1 );

// 填充才可以发送的定长消息 防止未填充就发送
CFZLCommon_Msg_2 Msg_2;
Msg_2.Fill( 3 );
Send( &Msg_2 );

// 填充才可以发送的变长消息  
CFZLCommon_Msg_3 Msg_3;
Msg_2.Fill_P( 5 );
Send( &Msg_3 );
//*/


/* 压缩消息形式
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
	// 类型
	WORD	m_wType;	
	// 长度（包括基本消息）   
	WORD	m_wSize;		

public:
	// 为最后一个字符串成员补齐字符串结束符
	void	PadNT( void );
	void	WPadNT( void );

	// 将长度<256的字符串序列化
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
	// 序列化数据
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
	// 获取指定位置的指针
	template<typename T_ValueType>
	T_ValueType* const	GetValuePtr(
							BYTE const * const		pData
							, DWORD&			dwPos		
							);
	// 将数值序列化
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
	// <消息类型, <消息最小size， 消息最大size>>
	typedef vector< pair<DWORD, DWORD> > TypeMap;


public:
	// 所有注册的消息
	TypeMap	m_Msgs;	


public:
	// 消息类型dwType 
	bool const	Sign(
					DWORD const		dwMsgType
					, DWORD const	dwMsgMaxSize
					, DWORD const	dwMsgMinSize = sizeof( CFBNetwork_Parser_Msg )
					);
	// 注册消息MSG_TYPE
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
	有时候处理到某个消息之后就要走其他流程，暂停后面的消息处理，然后其他流程走完在继续处理消息，就要用到这个函数
	*/
	void		Break(DWORD dwLastProcessedMsg);

public:
	DWORD										m_dwBuffers;	// 处理缓冲区大小
	CFBKernel_Vector<char>						m_Buffer;		// 处理缓冲区
	DWORD										m_dwOffset;		// 处理缓冲区起始位置

	CFBKernel_Vector<CFBNetwork_Parser_Msg* >	m_Msgs;			// 分析出来的消息


public:
				CFBNetwork_Parser( );
				~CFBNetwork_Parser( );
};



template<typename MSG_TYPE>
bool const
CFBNetwork_Parser_Signer::Sign( void )
{
	BOOST_STATIC_ASSERT(static_cast<DWORD>( MSG_TYPE::TYPE ) <= static_cast<DWORD>( USHRT_MAX ));
	// 防止消息超过大小表示
	BOOST_STATIC_ASSERT(static_cast<DWORD>( sizeof( MSG_TYPE ) ) <= static_cast<DWORD>( USHRT_MAX ));
	BOOST_STATIC_ASSERT(static_cast<DWORD>( MSG_TYPE::MIN_SIZE ) <= static_cast<DWORD>( sizeof( MSG_TYPE ) ));
	BOOST_STATIC_ASSERT(static_cast<DWORD>( MSG_TYPE::MIN_SIZE ) >= static_cast<DWORD>( sizeof( CFBNetwork_Parser_Msg ) ));

	DWORD const dwType	= static_cast<DWORD>( MSG_TYPE::TYPE );
	DWORD const dwMaxSize = static_cast<DWORD>( sizeof( MSG_TYPE ) );
	DWORD const dwMinSize = static_cast<DWORD>( MSG_TYPE::MIN_SIZE );

	return Sign(dwType, dwMaxSize, dwMinSize);
}
