#pragma once

#ifdef D_BSN_IS_DLL_plug_one
	#define D_BSN_plug_one_DLL D_DllCExport
#else
	#define D_BSN_plug_one_DLL D_DllCImport

	#if (defined WIN32)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_plug_one_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_plug_one.lib")
		#endif
	#endif
#endif


