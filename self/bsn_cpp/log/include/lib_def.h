#pragma once

#ifdef D_BSN_log_IS_DLL
	#define D_BSN_log_DLL D_DllExport
#else
	#define D_BSN_log_DLL D_DllImport
	#ifdef _DEBUG
		#pragma comment(lib, "lib_bsn_log_d.lib")
	#else
		#pragma comment(lib, "lib_bsn_log.lib")
	#endif
#endif


