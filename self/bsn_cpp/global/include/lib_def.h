#pragma once

#ifdef D_BSN_global_IS_DLL
	#define D_BSN_Global_DLL D_DllExport
#else
	#define D_BSN_Global_DLL D_DllImport
	#ifdef _DEBUG
		#pragma comment(lib, "lib_bsn_Global_d.lib")
	#else
		#pragma comment(lib, "lib_bsn_Global.lib")
	#endif
#endif


