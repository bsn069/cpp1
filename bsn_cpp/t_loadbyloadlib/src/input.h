#pragma once

#include "./../include/i_input.h"
 
#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/log/include/i_log.h>

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
	void 
		SetLib(D_N1(load_lib)::I_Lib::T_SPI_Lib spI_Lib);
	T_SPI_Input
		GetSPI_Input();

public:
	C_Input();
	virtual ~C_Input();

private:
	D_N1(load_lib)::I_Lib::T_SPI_Lib 	m_spI_Lib;
	D_N1(log)::I_Log::T_SPI_Log 		m_spI_Log;
};
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End