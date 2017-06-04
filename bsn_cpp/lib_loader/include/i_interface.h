#pragma once
#include <stdint.h>
#include <bsn_cpp/include/name_space.h>
#include <bsn_cpp/include/i_lib_interface.h>
#include <bsn_cpp/include/define.h>

#include <memory>

D_BsnNamespace1(lib_loader)
//////////////////////////////////////////////////////////////////////
class I_Lib
{
public:
	typedef std::shared_ptr<I_Lib> T_SharePtr;

public:
	virtual void* 	Func(const char* strFuncName) = 0;
};


class I_Interface : public I_LibInterface
{
public:
	typedef std::shared_ptr<I_Interface> T_SharePtr;

public:
	// /media/sf_/github/cpp1/bsn_cpp/out/libbsn_dlib_log_d.so
	// export LD_LIBRARY_PATH="/media/sf_/github/cpp1/bsn_cpp/out"
	// p->Open("bsn_dlib_log", "_d", "", 0);
	virtual I_Lib::T_SharePtr	Load(
		const char* strLibPath
		, const char* strLibName
	) = 0;
	virtual I_Lib::T_SharePtr	Get(const char* strLibName) = 0;
};
typedef D_FunDef I_Interface::T_SharePtr	(*T_FuncCreate)();
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


