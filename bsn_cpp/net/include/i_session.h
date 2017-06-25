#pragma once
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/i_lib_interface.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/buffer.hpp>
#include <memory>
#include <list>
 
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
class I_Session : public std::enable_shared_from_this<I_Session>
{
public:
	typedef std::shared_ptr<I_Session> T_SharePtrISession;
 	enum E_State : uint8_t
	{
		E_State_Close	= 0,
		E_State_WaitingOrConnecting,
		E_State_Established,
	};
	typedef std::list<I_Buffer*> T_RecvBuffers;
	
public:
	virtual E_State State() = 0;
	virtual bool Send(uint8_t* pData, uint32_t uLen) = 0;
	virtual bool SendEnd();
	virtual bool Recv(T_RecvBuffers& buffers) = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


