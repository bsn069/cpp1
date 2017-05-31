#pragma once

#ifdef D_BSN_console_input_IS_DLL
	#define D_BSN_console_input_DLL D_DllExport
#else
	#define D_BSN_console_input_DLL D_DllImport
	#ifdef _DEBUG
		#pragma comment(lib, "lib_bsn_console_input_d.lib")
	#else
		#pragma comment(lib, "lib_bsn_console_input.lib")
	#endif
#endif


