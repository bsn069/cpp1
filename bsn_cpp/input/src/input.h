#pragma once

#include "./../include/i_input.h"
 
#include <bsn_cpp/global/include/i_global.h>
#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/log/include/i_log.h>

#include <bsn_cpp/include/double_list.hpp>
 
#include <thread>
 

D_BsnNamespace1(input)
//////////////////////////////////////////////////////////////////////
class C_Input : public I_Input {
public:
	typedef std::shared_ptr<C_Input> T_SPC_Input;	

public:
 	static T_SPC_Input
		NewC_Input();
	static T_SPI_Input
		NewI_Input();

public:
	virtual void
		Init() override;
	virtual void
		Start() override;
	virtual void
		Quit() override;
	virtual void
		UnInit() override;
	virtual T_Cmds* 
		GetCmds() override;

	virtual void 
		DebugInfo() override;

public:
	T_SPI_Input
		GetSPI_Input();
	T_SPC_Input
		GetSPC_Input();

	void
		InputThread();
	void 
		SetGlobal(D_N1(global)::I_Global::T_SPI_Global spI_Global);

public:
	C_Input();
	virtual ~C_Input();

private:
	D_N1(global)::I_Global::T_SPI_Global m_spI_Global;
	D_N1(log)::I_Log::T_SPI_Log 		m_spI_Log;
	std::thread* m_pThread;
	bool m_bQuit;
	C_DoubleList<T_Cmds> m_InputCmd;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End