#pragma once

#ifdef D_BSN_IS_DLL_common
	#define D_BSN_common_DLL D_DllExport
#else
	#define D_BSN_common_DLL D_DllImport

	#if (defined WIN32)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_common_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_common.lib")
		#endif
	#endif
#endif


