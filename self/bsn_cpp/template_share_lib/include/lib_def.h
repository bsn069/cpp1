#pragma once

#ifdef D_BSN_template_share_lib_IS_DLL
	#define D_BSN_template_share_lib_DLL D_DllExport
#else
	#define D_BSN_template_share_lib_DLL D_DllImport
	#ifdef _DEBUG
		#pragma comment(lib, "lib_bsn_template_share_lib_d.lib")
	#else
		#pragma comment(lib, "lib_bsn_template_share_lib.lib")
	#endif
#endif


