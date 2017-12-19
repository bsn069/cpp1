#include "./input.h"

#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/global/include/i_global.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(input)
//////////////////////////////////////////////////////////////////////

D_DllCExport I_Input::T_SPI_Input 
NewInput(
	D_N1(load_lib)::I_Lib::T_SPI_Lib spI_Lib
) {
	auto spC_Input = C_Input::NewC_Input();
	spC_Input->SetLib(spI_Lib);
	
	return spC_Input->GetSPI_Input();
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
