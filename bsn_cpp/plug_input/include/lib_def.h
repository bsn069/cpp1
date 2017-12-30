#pragma once

#ifdef D_BSN_IS_DLL_plug_input
	#define D_BSN_plug_input_DLL D_DllCExport
#else
	#define D_BSN_plug_input_DLL D_DllCImport

	#if (defined WIN32)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_plug_input_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_plug_input.lib")
		#endif
	#endif
#endif


