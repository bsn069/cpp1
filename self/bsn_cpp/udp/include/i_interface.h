#pragma once

#include <bsn/include/port.h>
#include "./lib_def.h"

D_BsnNamespace1(UDP)
//////////////////////////////////////////////////////////////////////
class I_Interface
{
public:
	friend D_BSN_udp_DLL T_void Release(I_Interface* pTemplate);


protected:
	virtual ~I_Interface(){};


public:
	virtual T_wchar D_const* D_const Name() D_const = 0;
	virtual T_wchar D_const* D_const Error(T_int32 D_const i32ErrorCode) D_const = 0;

	virtual T_int32 D_const	Bind(
		T_wchar D_const * D_const	pwcIP
		, T_uint16 D_const			u16Port
		) = 0;
	virtual T_int32 D_const	Recv(
		T_byte *  					pbyData
		, T_uint32 D_const			u32Len
		, std::size_t&				stLen
		) = 0;
	virtual T_int32 D_const	Send(
		T_byte D_const * D_const	pbyData
		, T_uint32 D_const			u32Len
		, std::size_t&				stLen
		) = 0;
	virtual T_int32 D_const	SetSendAddr(
		T_wchar D_const * D_const	pwcIP
		, T_uint16 D_const			u16Port
		) = 0;
};


D_FunDef D_BSN_udp_DLL I_Interface*	Create();
D_FunDef D_BSN_udp_DLL T_void		Release(I_Interface* pInterface);
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


