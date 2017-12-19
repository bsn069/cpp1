#pragma once

#ifdef D_BSN_IS_DLL_input
	#define D_BSN_input_DLL D_DllExport
#else
	#define D_BSN_input_DLL D_DllImport

	#if (defined WIN32)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_input_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_input.lib")
		#endif
	#endif
#endif


