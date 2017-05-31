#pragma once
#include "./main.h"
D_BsnNamespace1(Log)
//////////////////////////////////////////////////////////////////////

class C_Interface : public I_Interface
{
public:
	typedef vector<wstring> T_Logs;

public:
	virtual T_wchar D_const * D_const Name() D_const override;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const override;

	// 输出日志级别
	virtual T_int32 D_const	SetLevelOutput(T_Level D_const Level) override;
	virtual T_int32 D_const GetLevelOutput(T_Level& Level) D_const override;

	// 保存日志级别
	virtual T_int32 D_const	SetLevelLog(T_Level D_const Level) override;
	virtual T_int32 D_const GetLevelLog(T_Level& Level) D_const override;

	// 设置日志处理回调函数
	virtual T_int32 D_const	SetCallBackOutput(T_CallBack CallBack) override;
	virtual T_int32 D_const	SetCallBackLog(T_CallBack CallBack) override;

	virtual T_int32 D_const	Start() override;

	// 写日志
	virtual T_int32 D_const	Write(T_Level D_const Level, T_wchar D_const * D_const pwcLog) override;
	virtual T_int32 D_const	Write(
		T_wchar D_const * D_const pwcModule
		, T_Level D_const Level
		, T_wchar D_const * D_const pwcLog
		, T_wchar D_const * D_const pwcFile
		, T_wchar D_const * D_const pwcFunction
		, T_uint32 D_const u32Line
		) override;

	T_void Thread();

	T_void	Process();

	// 默认回调
	T_void CallBackOutput(T_Level D_const Level, wstring D_const& wstrLog);
	T_void CallBackLog(T_Level D_const Level, wstring D_const& wstrLog);


public:
	C_Interface();
	virtual ~C_Interface();

private:
	C_DoubleList<T_Logs> m_Output;
	thread* m_pThread;
	volatile T_bool m_bQuit;
	T_Level m_LevelOutput;
	T_Level m_LevelLog;
	T_CallBack m_CallBackOutput;
	T_CallBack m_CallBackLog;
};

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End