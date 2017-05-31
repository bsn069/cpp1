#pragma once
D_BsnNamespace1(ConsoleInput)
//////////////////////////////////////////////////////////////////////

class I_Interface
{
public:
	typedef vector<wstring> T_Cmds;


protected:
	virtual ~I_Interface() {};


public:
	virtual T_wchar D_const* D_const Name() D_const = 0;
	virtual T_wchar D_const* D_const Error(T_int32 D_const i32ErrorCode) D_const = 0;

	virtual T_int32 D_const	Start() = 0;
	virtual T_Cmds* GetCmds() = 0;
	virtual T_bool D_const IsQuit() D_const = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End


