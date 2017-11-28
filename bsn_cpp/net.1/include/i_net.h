#pragma once
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/i_lib_interface.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/buffer.hpp>
#include <memory>
#include <list>
#include "i_session.h"
 
D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
class I_Net
{
public:
	typedef std::shared_ptr<I_Net> 			T_SharePtrINet;
	typedef I_Session::T_SharePtrISession 	T_SharePtrISession;
	// typedef std::list<T_SharePtrISession>	T_AcceptISessions;
	
public:
	virtual bool Listen(std::string strIp, uint16_t u16Port) = 0;
	virtual T_SharePtrISession GetAcceptSession();

	virtual T_SharePtrISession Connect(std::string strIp, uint16_t u16Port) = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

