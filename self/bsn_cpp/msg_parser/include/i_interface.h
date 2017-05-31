#pragma once
D_BsnNamespace1(MsgParser)
//////////////////////////////////////////////////////////////////////

class I_Interface
{
public:
	typedef C_MsgHeader<T_uint16, T_uint16> T_MsgHeader;
	typedef vector<T_MsgHeader*> T_Msgs;
	typedef vector<I_Buffer*> T_Buffers;


protected:
	virtual ~I_Interface() = default;


public:
	virtual T_wchar D_const* D_const Name() D_const = 0;
	virtual T_wchar D_const* D_const Error(T_int32 D_const i32ErrorCode) D_const = 0;

	virtual T_int32 D_const IncSize(T_uint32 D_const u32IncSize) = 0;
	virtual T_int32 D_const Push(T_Buffers D_const * D_const pBuffers) = 0;
	virtual T_int32 D_const	Msgs(T_Msgs D_const*& pMsgs) D_const = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


