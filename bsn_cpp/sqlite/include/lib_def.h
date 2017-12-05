#pragma once

#ifdef D_BSN_IS_DLL_sqlite
	#define D_BSN_sqlite_DLL D_DllExport
#else
	#define D_BSN_sqlite_DLL D_DllImport

	#if (defined WIN32)
		#ifdef _DEBUG
			#pragma comment(lib, "bsn_dlib_sqlite_d.lib")
		#else
			#pragma comment(lib, "bsn_dlib_sqlite.lib")
		#endif
	#endif
#endif


