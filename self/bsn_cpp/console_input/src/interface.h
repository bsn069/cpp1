#pragma once
#include "./main.h"
D_BsnNamespace1(ConsoleInput)
//////////////////////////////////////////////////////////////////////

class C_Interface : public I_Interface
{
public:

public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;

	virtual T_int32 D_const	Start() override;
	virtual T_Cmds* GetCmds() override;
	virtual T_bool D_const IsQuit() D_const override;


public:
	T_void Thread();


public:
	C_DoubleList<T_Cmds> m_Output;
	thread* m_pThread;
	volatile T_bool m_bQuit;


public:
	C_Interface();
	virtual ~C_Interface();
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End