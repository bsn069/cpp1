#include "./log.h"

#include <bsn_cpp/load_lib/include/i_lib.h>

#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(log)
//////////////////////////////////////////////////////////////////////

C_DB* 
CreateCDB() {
	C_DB* imp = New<C_DB>();
	return imp;
}


void 
ReleaseCDB(I_DB* iDB) {
	C_DB* pImp = static_cast<C_DB*>(iDB);
	Delete(pImp);
}

D_DllExport I_DB::T_SPI_DB 
NewDB(
	D_N1(load_lib)::I_Lib::T_SPI_Lib spI_Lib
	, D_N1(log)::I_Log::T_SPI_Log spI_Log
) {
	auto pSelfI = I_DB::T_SPI_DB(
		CreateCDB()
		, ReleaseCDB
	);
	auto pSelfC = std::dynamic_pointer_cast<C_DB>(pSelfI);
	pSelfC->SetLib(spI_Lib);
	pSelfC->SetLog(spI_Log);
	
	return pSelfI;
}


//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
