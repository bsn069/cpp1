#include "input.h"

#include <bsn_cpp/log/include/d_log.h>
#include <bsn_cpp/global/include/i_global.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

#include <boost/bind.hpp>

D_BsnNamespace1(input)
//////////////////////////////////////////////////////////////////////
C_Input::C_Input() 
	: m_spI_Lib(nullptr) 
	, m_spI_Log(nullptr)
	, m_pThread(nullptr)
	, m_bQuit(false)
{

}

C_Input::~C_Input() {
	m_spI_Log	= nullptr;
	m_spI_Lib 	= nullptr;
}

void 
C_Input::Init() {
	D_LogInfo(m_spI_Log, "enter input Init");
	
	D_LogInfo(m_spI_Log, "leave input Init");
}

void 
C_Input::Start() {
	D_LogInfo(m_spI_Log, "enter input Start");

 	if (m_pThread != nullptr) {
		return;
	}
	m_pThread = New<std::thread>(boost::bind(&C_Input::InputThread, this));

	D_LogInfo(m_spI_Log, "leave input Start");
}

void
C_Input::Quit() {
	D_LogInfo(m_spI_Log, "enter input Quit");

	if (m_pThread != nullptr) {
		m_bQuit = true;
		D_LogInfo(m_spI_Log, "wait input thread end");
		m_pThread->join();
		D_LogInfo(m_spI_Log, "input thread end");
		Delete(m_pThread);
	}

	D_LogInfo(m_spI_Log, "leave input Quit");
}

void 
C_Input::UnInit() {
	D_LogInfo(m_spI_Log, "enter input UnInit");

	D_LogInfo(m_spI_Log, "leave input UnInit");
}

I_Input::T_Cmds*
C_Input::GetCmds() {
	return &(m_InputCmd.Flip());
}


void 
C_Input::SetLib(D_N1(load_lib)::I_Lib::T_SPI_Lib spI_Lib)	{
	m_spI_Lib = spI_Lib;
	m_spI_Log = spI_Lib->GetGlobal()->GetLog();
}

C_Input::T_SPI_Input
C_Input::GetSPI_Input() {
	return shared_from_this();
}

C_Input::T_SPC_Input
C_Input::GetSPC_Input() {
	auto spI_Input = GetSPI_Input();
	auto spC_Input = std::dynamic_pointer_cast<C_Input>(spI_Input);
 	return spC_Input;
}

void
C_Input::InputThread() {
	D_LogInfo(m_spI_Log, "enter input thread");
	std::string strCmd;
	char cInput;

	while (!m_bQuit) {
		D_LogInfo(m_spI_Log, "wait input");
		strCmd.clear();
		while ((cInput = getchar()) != '\n') {
			strCmd += cInput;
		}
		m_InputCmd.Write(strCmd);
	}
	D_LogInfo(m_spI_Log, "leave input thread");
}

//////////////////////////////////////////////////////////////////////
C_Input* 
CreateCInput() {
	C_Input* imp = New<C_Input>();
	return imp;
}

void 
ReleaseCInput(I_Input* iInput) {
	C_Input* pImp = static_cast<C_Input*>(iInput);
	Delete(pImp);
}

C_Input::T_SPC_Input
C_Input::NewC_Input() {
	auto spC_Input = C_Input::T_SPC_Input(
		CreateCInput()
		, ReleaseCInput
	);
	return spC_Input;
}

C_Input::T_SPI_Input
C_Input::NewI_Input() {
	auto spC_Input = C_Input::NewC_Input();
	return spC_Input->GetSPI_Input();
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End

#if (defined WIN32)

#else
 
#endif