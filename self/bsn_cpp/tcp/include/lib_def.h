#pragma once


#ifdef D_BSN_tcp_IS_DLL
	#define D_BSN_tcp_DLL D_DllExport
#else
	#define D_BSN_tcp_DLL D_DllImport
	#ifdef _DEBUG
		#pragma comment(lib, "lib_bsn_tcp_d.lib")
	#else
		#pragma comment(lib, "lib_bsn_tcp.lib")
	#endif
#endif

