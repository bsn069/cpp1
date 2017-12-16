#pragma once

#include <bsn_cpp/include/define.h>


#ifdef D_BSN_IS_DLL_global
	#define D_BSN_global_DLL D_DllExport
#else
	#define D_BSN_global_DLL D_DllImport

	#if (defined WIN32)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_global_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_global.lib")
		#endif
	#endif
#endif


