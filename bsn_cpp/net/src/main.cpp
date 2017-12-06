#include "net.h"


#include <bsn_cpp/load_lib/include/i_lib.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>


D_BsnNamespace1(net)
//////////////////////////////////////////////////////////////////////

D_FunImp C_Net* 
CreateCNet(boost::asio::io_service& io) {
	C_Net* imp = New<C_Net>(io);
	return imp;
}


D_FunImp void 
ReleaseCNet(I_Net* iNet) {
	C_Net* pImp = static_cast<C_Net*>(iNet);
	Delete(pImp);
}

D_FunImp D_DllCExport I_Net::T_SPI_Net 
NewNet(
	D_N1(load_lib)::I_Lib::T_SPI_Lib	spI_Lib
	, boost::asio::io_service& io
) {
	auto p = CreateCNet(io);
	p->SetLib(spI_Lib);
	return I_Net::T_SPI_Net(p, ReleaseCNet);
}

//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
