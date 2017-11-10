#pragma once

#ifdef D_BSN_IS_DLL_net
	#define D_BSN_net_DLL D_DllExport
#else
	#define D_BSN_net_DLL D_DllImport

	#if (defined WIN32)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_net_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_net.lib")
		#endif
	#endif
#endif


