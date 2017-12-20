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

C_Log::C_Log()
{

}

C_Log::~C_Log()
{
	m_iLib = nullptr;
}

void 
C_Log::Init() {
	D_LogInfo(
		this
		, "enter load lib Init"
	);

	D_LogInfo(
		this
		, "leave load lib Init"
	);
}

void 
C_Log::Start() {
	D_LogInfo(
		this
		, "enter load lib Start"
	);

	D_LogInfo(
		this
		, "leave load lib Start"
	);
}

void 
C_Log::Quit() {
	D_LogInfo(
		this
		, "enter load lib Quit"
	);

	D_LogInfoF(
		this
		, "m_Libs.size()=%u"
		, m_Libs.size()
	);
	for (auto pair : m_Libs) {
		m_WaitDelLibs.push_back(pair.second);
		D_LogInfo(
			this
			, pair.first.c_str()
		);
	}

	D_LogInfo(
		this
		, "leave load lib Quit"
	);
}

void	
C_Log::UnInit() {
	D_LogInfo(
		this
		, "enter load lib UnInit"
	);

	D_LogInfo(
		this
		, "leave load lib UnInit"
	);
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
	#include "./linux/log.ipp"
#endif