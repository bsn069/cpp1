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
	Print(eLevel, strLog);
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
	FmtPrint(eLevel, strLog, args);	
	va_end(args);
}

C_Log::C_Log()
{

}

C_Log::~C_Log()
{
	m_iLib = nullptr;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
	#include "./linux/log.ipp"
#endif