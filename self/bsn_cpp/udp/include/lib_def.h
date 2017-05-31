#pragma once


//////////////////////////////////////////////////////////////////////
#ifdef D_BSN_udp_IS_DLL
	#define D_BSN_udp_DLL D_DllExport
#else
	#define D_BSN_udp_DLL D_DllImport
	#ifdef _DEBUG
		#pragma comment(lib, "lib_bsn_udp_d.lib")
	#else
		#pragma comment(lib, "lib_bsn_udp.lib")
	#endif
#endif
//////////////////////////////////////////////////////////////////////

