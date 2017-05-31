#pragma once


#ifdef D_BSN_service_tcp_client_IS_DLL
	#define D_BSN_service_tcp_client_DLL D_DllCExport
#else
	#define D_BSN_service_tcp_client_DLL D_DllCImport
	#ifdef _DEBUG
		#pragma comment(lib, "lib_bsn_service_tcp_client_d.lib")
	#else
		#pragma comment(lib, "lib_bsn_service_tcp_client.lib")
	#endif
#endif

