#pragma once

#ifdef D_BSN_IS_DLL_log
	#define D_BSN_log_DLL D_DllExport
#else
	#define D_BSN_log_DLL D_DllImport

	#if (defined WIN32)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_log_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_log.lib")
		#endif
	#endif
#endif


