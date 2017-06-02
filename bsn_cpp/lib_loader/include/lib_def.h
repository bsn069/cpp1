#pragma once

#ifdef D_BSN_IS_DLL_lib_loader
	#define D_BSN_lib_loader_DLL D_DllExport
#else
	#define D_BSN_lib_loader_DLL D_DllImport

	#if (defined WIN32)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_lib_loader_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_lib_loader.lib")
		#endif
	#endif
#endif


