#pragma once
#include <bsn/msg_parser/include/i_interface.h>
D_BsnNamespace1(Other)
//////////////////////////////////////////////////////////////////////

class C_MgrUser;
class C_User
{
public:
	typedef T_uint32						T_ID;
	typedef D_N1(MsgParser)::I_Interface	T_MsgParser;
	typedef T_MsgParser::T_Msgs				T_Msgs;
	
	// ÎÞÐ§ID
	static T_ID D_const msc_IDNull = 0;


public:
	T_ID&				ID(){return m_ID;};
	T_Msgs D_const*&	Msgs(){return m_pMsgs;};

	virtual T_int32 D_const	Update();
	virtual T_int32 D_const	ProcMsg() = 0;
	virtual T_int32 D_const	RecvMsg() = 0;

	T_int32 D_const	SetMgrUser(C_MgrUser* pMgrUser);
	C_MgrUser*		GetMgrUser();

	T_int32 D_const	CreateMsgParser();
	T_int32 D_const	ReleaseMsgParser();

public:
	C_User();
	~C_User();


protected:
	T_MsgParser*	m_pMsgParser;
	T_Msgs D_const*	m_pMsgs;
	T_ID			m_ID;
	C_MgrUser*		m_pMgrUser;
};
 
 

D_BsnNamespace1End
