#pragma once
#include "i_net.h"
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/i_lib_interface_ex.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////
class I_Interface : public I_LibInterfaceEx,  public std::enable_shared_from_this<I_Interface>
{
public:
	typedef std::shared_ptr<I_Interface> T_SharePtr;
	typedef I_Net::T_SharePtrINet T_SharePtrINet;
	
public:
	virtual T_SharePtrINet Create() = 0;
	virtual void Release(T_SharePtrINet pINet) = 0;
};
typedef D_FunDef I_Interface::T_SharePtr	(*T_FuncCreate)(I_Interface::T_SharePtrLib);
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


