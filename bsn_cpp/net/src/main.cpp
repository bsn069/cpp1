#include "./net.h"


#include <bsn_cpp/load_lib/include/i_lib.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>


D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////

D_FunImp C_Net* CreateCNet()
{
	C_Net* imp = New<C_Net>();
	return imp;
}


D_FunImp void ReleaseINet(I_Net* iNet)
{
	C_Net* pImp = static_cast<C_Net*>(iNet);
	Delete(pImp);
}

D_FunImp D_DllExport I_Net::T_SPI_Net Create(D_N1(load_lib)::I_Lib::T_SPI_Lib iLib)
{
	auto p = C_Net::T_SPC_Net(CreateCNet(), ReleaseINet);
	p->SetLib(iLib);
	
	auto pSelfC = std::dynamic_pointer_cast<I_Net>(p);
	return pSelfC;
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
