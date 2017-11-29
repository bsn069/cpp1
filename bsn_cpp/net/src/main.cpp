#include "./net.h"


#include <bsn_cpp/load_lib/include/i_lib.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>


D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////

D_FunImp C_Net* 
CreateCNet() {
	C_Net* imp = New<C_Net>();
	return imp;
}


D_FunImp void 
ReleaseCNet(I_Net* iNet) {
	C_Net* pImp = static_cast<C_Net*>(iNet);
	Delete(pImp);
}

D_FunImp D_DllExport I_Net::T_SPI_Net 
Create(
	D_N1(load_lib)::I_Lib::T_SPI_Lib	spI_Lib
	, D_N1(common)::T_SPI_Common 		spI_Common
) {
	auto p = CreateCNet();
	p->SetLib(spI_Lib);
	p->SetCommon(spI_Common);	
	return I_Net::T_SPI_Net(p, ReleaseCNet);
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
