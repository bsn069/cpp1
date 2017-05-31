#pragma once


#ifdef D_BSN_common_IS_DLL
	#define D_BSN_common_DLL D_DllExport
#else
	#define D_BSN_common_DLL D_DllImport
	#ifdef _DEBUG
		#pragma comment(lib, "lib_bsn_common_d.lib")
	#else
		#pragma comment(lib, "lib_bsn_common.lib")
	#endif
#endif

