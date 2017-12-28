#include "./input.h"

#include <bsn_cpp/global/include/i_global.h>
 

D_BsnNamespace1(input)
//////////////////////////////////////////////////////////////////////

D_FunImp D_DllExport I_Input::T_SPI_Input 
NewInput(
	D_N1(global)::I_Global::T_SPI_Global spI_Global
) {
	auto spC_Input = C_Input::NewC_Input();
	spC_Input->SetGlobal(spI_Global);
	
	return spC_Input->GetSPI_Input();
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
