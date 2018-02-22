#include <bsn_cpp/plug_node/src/plug.h>

#include <bsn_cpp/include/d_out.h>
#include <bsn_cpp/include/new.hpp>
#include <bsn_cpp/include/delete.hpp>

D_BsnNamespace1(plug_node)
//////////////////////////////////////////////////////////////////////
C_Plug* CreateC_Plug(void* pData) {
	D_OutInfo();
	C_Plug* pC_Plug = New<C_Plug>(pData);
	return pC_Plug;
}

void ReleaseC_Plug(D_N1(plug_mgr)::I_Plug* pI_Plug) {
	D_OutInfo();
	C_Plug* pC_Plug = static_cast<C_Plug*>(pI_Plug);
	Delete(pC_Plug);
}

C_Plug::T_SPC_Plug C_Plug::NewC_Plug(void* pData) {
	D_OutInfo();
	auto pC_Plug = CreateC_Plug(pData);
	auto spC_Plug = C_Plug::T_SPC_Plug(pC_Plug, ReleaseC_Plug);
	return spC_Plug;
}

D_N1(plug_mgr)::I_Plug::T_SPI_Plug C_Plug::NewI_Plug(void* pData) {
	D_OutInfo();
	auto spC_Plug = C_Plug::NewC_Plug(pData);
	auto spI_Plug = spC_Plug->GetSPI_Plug();
	return spI_Plug;
}
//////////////////////////////////////////////////////////////////////
D_BsnNamespace1End
 