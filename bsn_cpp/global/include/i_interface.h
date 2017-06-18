#pragma once
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/i_lib_interface.h>
#include <bsn_cpp/include/define.h>

#include <bsn_cpp/lib_loader/include/i_interface.h>
#include <bsn_cpp/log/include/i_interface.h>
#include <bsn_cpp/log/include/i_log.h>

D_BsnNamespace1(global)
//////////////////////////////////////////////////////////////////////
class I_Interface : public I_LibInterface,  public std::enable_shared_from_this<I_Interface>
{
public:
	typedef std::shared_ptr<I_Interface> T_SharePtr;
	typedef D_N1(lib_loader)::I_Interface::T_SharePtr T_SharePtrLibLoader;
	typedef D_N1(log)::I_Log::T_SharePtr T_SharePtrLog;
	typedef D_N1(log)::I_Interface::T_SharePtr T_SharePtrLogInterace;

public:
	virtual void Start(int argc, char* argv[]) = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


