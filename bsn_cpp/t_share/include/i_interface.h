#pragma once
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/i_lib_interface.h>
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/lib_loader/include/i_interface.h>

#include <memory>
#include <iostream>

D_BsnNamespace1(t_share)
//////////////////////////////////////////////////////////////////////

class I_Interface : public I_LibInterface
{
public:
	typedef std::shared_ptr<I_Interface> T_SharePtr;
	typedef D_N1(lib_loader)::I_Interface::T_SharePtr T_SharePtrLibLoader;
	
public:
	virtual void SetLibLoader(T_SharePtrLibLoader lib_loader) {};

};
typedef D_FunDef I_Interface::T_SharePtr	(*T_FuncCreate)(I_Interface::T_SharePtrLibLoader);
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


