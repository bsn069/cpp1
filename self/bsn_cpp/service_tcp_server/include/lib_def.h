#pragma once


#ifdef D_BSN_service_tcp_server_IS_DLL
	#define D_BSN_service_tcp_server_DLL D_DllCExport
#else
	#define D_BSN_service_tcp_server_DLL D_DllCImport
	#ifdef _DEBUG
		#pragma comment(lib, "lib_bsn_service_tcp_server_d.lib")
	#else
		#pragma comment(lib, "lib_bsn_service_tcp_server.lib")
	#endif
#endif

