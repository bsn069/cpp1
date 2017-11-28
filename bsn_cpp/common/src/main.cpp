#include "./common.h"

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(common)
//////////////////////////////////////////////////////////////////////

D_FunImp I_Common* 
CreateCCommon() {
	C_Common* imp = New<C_Common>();
	return imp;
}


D_FunImp void 
ReleaseCCommon(I_Common* iCommon) {
	C_Common* pImp = static_cast<C_Common*>(iCommon);
	Delete(pImp);
}


D_FunImp D_DllExport I_Common::T_SPI_Common 
Create() {
	auto p = I_Common::T_SPI_Common(CreateCCommon(), ReleaseCCommon);
	return p;
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
