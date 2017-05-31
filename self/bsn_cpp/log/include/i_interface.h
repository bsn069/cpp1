#pragma once
D_BsnNamespace1(Log)
//////////////////////////////////////////////////////////////////////

class I_Interface
{
public:
	// ��־���� ��λ
	typedef T_uint32 T_Level;
	// ��־������
	typedef function<T_void(T_Level D_const Level, wstring D_const& wstrLog)> T_CallBack;


protected:
	virtual ~I_Interface() {};


public:
	virtual T_wchar D_const * D_const Name() D_const = 0;
	virtual T_wchar D_const * D_const Error(T_int32 D_const i32ErrorCode) D_const = 0;

	// �����־����
	virtual T_int32 D_const	SetLevelOutput(T_Level D_const Level) = 0;
	virtual T_int32 D_const GetLevelOutput(T_Level& Level) D_const = 0;
	
	// ������־����
	virtual T_int32 D_const	SetLevelLog(T_Level D_const Level) = 0;
	virtual T_int32 D_const GetLevelLog(T_Level& Level) D_const = 0;

	// ������־����ص�����
	virtual T_int32 D_const	SetCallBackOutput(T_CallBack CallBack) = 0;
	virtual T_int32 D_const	SetCallBackLog(T_CallBack CallBack) = 0;

	// ������־����
	virtual T_int32 D_const	Start() = 0;

	// д��־
	virtual T_int32 D_const	Write(T_Level D_const Level, T_wchar D_const * D_const pwcLog) = 0;
	virtual T_int32 D_const	Write(
		T_wchar D_const * D_const pwcModule
		, T_Level D_const Level
		, T_wchar D_const * D_const pwcLog
		, T_wchar D_const * D_const pwcFile
		, T_wchar D_const * D_const pwcFunction
		, T_uint32 D_const u32Line
		) = 0;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#define D_LogModuleLevel(pLog, pwcModule, Level, pwcLog) \
	pLog->Write(pwcModule, Level, pwcLog, __FILEW__, __FUNCTIONW__, __LINE__)

#define D_LogLevel(pLog, Level, pwcLog) D_LogModuleLevel(pLog, T_nullptr, Level, pwcLog)
#define D_Log(pLog, pwcLog) D_LogLevel(pLog, integer_traits<D_N1(Log)::I_Interface::T_Level>::const_max, pwcLog)


