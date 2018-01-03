#pragma once

#ifdef D_BSN_IS_DLL_plug_net
	#define D_BSN_plug_net_DLL D_DllCExport
#else
	#define D_BSN_plug_net_DLL D_DllCImport

	#if (defined WIN32)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_plug_net_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_plug_net.lib")
		#endif
	#endif
#endif


