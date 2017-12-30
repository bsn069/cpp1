#pragma once

#include <bsn_cpp/include/define.h>


#ifdef D_BSN_IS_DLL_plug_mgr
	#define D_BSN_plug_mgr_DLL D_DllExport
#else
	#define D_BSN_plug_mgr_DLL D_DllImport

	#if (defined WIN32)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_plug_mgr_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_plug_mgr.lib")
		#endif
	#endif
#endif


