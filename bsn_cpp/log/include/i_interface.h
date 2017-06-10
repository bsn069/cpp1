#pragma once
#include "i_log.h"
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/i_lib_interface.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/lib_loader/include/i_lib.h>

#include <stdint.h>
#include <memory>

D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////
class I_Interface : public I_LibInterface,  public std::enable_shared_from_this<I_Interface>
{
public:
	typedef std::shared_ptr<I_Interface> T_SharePtr;
	typedef D_N1(lib_loader)::I_Lib::T_SharePtr T_SharePtrLib;
	
public:
	virtual I_Log::T_SharePtr CreateLog(char const * const strName, void* pOwner) = 0;
	virtual void WaitQuit() = 0;
};
typedef D_FunDef I_Interface::T_SharePtr	(*T_FuncCreate)(I_Interface::T_SharePtrLib);
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


