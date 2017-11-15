#pragma once

#ifdef D_BSN_IS_DLL_load_lib
	#define D_BSN_load_lib_DLL D_DllExport
#else
	#define D_BSN_load_lib_DLL D_DllImport

	#if (defined WIN32)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_load_lib_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_load_lib.lib")
		#endif
	#endif
#endif


