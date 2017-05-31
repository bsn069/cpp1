
using D_N1(Other)::I_Service;
//////////////////////////////////////////////////////////////////////
D_BSN_service_DLL I_Service* Create()
{
	C_Service* pImp = New<C_Service>();
	return pImp;
}


D_BSN_service_DLL T_void Release(I_Service* pService)
{
	C_Service* pImp = static_cast<C_Service*>(pService);
	Delete(pImp);
}

