#pragma once
#include "define.h"
#include "name_space.h"
#include "i_lib_interface.h"

#include <bsn_cpp/lib_loader/include/i_lib.h>
#include <bsn_cpp/log/include/i_interface.h>

#include <stdint.h>
#include <memory>

namespace N_Bsn
{
//////////////////////////////////////////////////////////////////////
class I_LibInterfaceEx : public I_LibInterface
{
public:
	typedef D_N1(lib_loader)::I_Lib::T_SharePtr T_SharePtrLib;
	typedef D_N1(log)::I_Log::T_SharePtr 		T_SharePtrLog;

public:
	virtual void 	SetLog(T_SharePtrLog pLog) = 0;
	virtual void 	WaitQuit() = 0;
};
//////////////////////////////////////////////////////////////////////
}






