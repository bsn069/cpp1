#pragma once
#include <stdint.h>
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/i_lib_interface.h>
#include <bsn_cpp/include/define.h>

#include <memory>

D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////

class I_Interface : public I_LibInterface
{
public:
	typedef std::shared_ptr<I_Interface> T_SharePtr;

public:
	// /media/sf_/github/cpp1/bsn_cpp/out/libbsn_dlib_log_d.so
	// export LD_LIBRARY_PATH="/media/sf_/github/cpp1/bsn_cpp/out"
	// p->Open("bsn_dlib_log", "_d", "", 0);
	virtual bool   	Open(
		const char* strLib
		, const char* strDebugSuffix
		, const char* strReleaseSuffix
		, uint retryCount
	) = 0;
	virtual void	Close() = 0;
	virtual void* 	Func(const char* strFuncName) = 0;
};
typedef D_FunDef I_Interface::T_SharePtr	(*T_FuncCreate)();

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


