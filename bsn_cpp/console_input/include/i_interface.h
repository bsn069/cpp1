#pragma once
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/i_lib_interface.h>
#include <bsn_cpp/include/define.h>

#include <memory>
#include <iostream>

D_BsnNamespace1(console_input)
//////////////////////////////////////////////////////////////////////

class I_Interface : public I_LibInterface
{
public:
	typedef std::shared_ptr<I_Interface> T_SharePtr;
};
typedef D_FunDef I_Interface::T_SharePtr	(*T_FuncCreate)();
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


