#pragma once

#ifdef D_BSN_IS_DLL_t_share
	#define D_BSN_t_share_DLL D_DllExport
#else
	#define D_BSN_t_share_DLL D_DllImport

	#if (defined _MSC_VER)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_t_share_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_t_share.lib")
		#endif
	#endif
#endif


