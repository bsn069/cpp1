#include "./../include/d_log.h"
#include "./log.h"


D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////
static char const * const sc_logLevel2Name[] = {
	"Debug",
	"Info ",
	"Warn ",
	"Error"
};

void C_Log::Push(
	E_Level eLevel
	, char const * strFile
	, uint32_t u32Line
	, char const * strFunc
	, char const * strLog
)
{
	Print(eLevel, strFile, u32Line, strFunc, strLog);
}

void C_Log::PushF(
	E_Level eLevel
	, char const * strFile
	, uint32_t u32Line
	, char const * strFunc
	, char const * strLog
	, ...
)
{
	va_list args;
	va_start(args, strLog);
	FmtPrint(eLevel, strFile, u32Line, strFunc, strLog, args);	
	va_end(args);
}

C_Log::C_Log() {

}

C_Log::~C_Log() {
	m_spI_Lib = nullptr;
}

void 
C_Log::Init() {
	D_LogInfo(
		this
		, "enter log Init"
	);

	D_LogInfo(
		this
		, "leave log Init"
	);
}

void 
C_Log::Start() {
	D_LogInfo(
		this
		, "enter log Start"
	);

	D_LogInfo(
		this
		, "leave log Start"
	);
}

void 
C_Log::Quit() {
	D_LogInfo(
		this
		, "enter log Quit"
	);

	D_LogInfo(
		this
		, "leave log Quit"
	);
}

void	
C_Log::UnInit() {
	D_LogInfo(
		this
		, "enter log UnInit"
	);

	D_LogInfo(
		this
		, "leave log UnInit"
	);
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
	#include "./linux/log.ipp"
#endif