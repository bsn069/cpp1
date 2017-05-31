#pragma once
#include "./main.h"
D_BsnNamespace1(MsgParser)
//////////////////////////////////////////////////////////////////////

class C_Interface : public I_Interface
{
public:
	static D_const T_uint32 msc_incSize = 512;

public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;
	
	virtual T_int32 D_const IncSize(T_uint32 D_const u32IncSize) override;
	virtual T_int32 D_const Push(T_Buffers D_const * D_const pBuffers) override;
	virtual T_int32 D_const	Msgs(T_Msgs D_const*& pMsgs) D_const override;


public:
	T_byte*		m_pBuffer;
	T_uint32	m_u32BufferSize;
	T_uint32	m_u32IncSize;

	T_uint32	m_u32Offset;
	T_uint32	m_u32Len;

	T_Msgs		m_Msgs;

public:
	C_Interface();
	virtual ~C_Interface();


};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End