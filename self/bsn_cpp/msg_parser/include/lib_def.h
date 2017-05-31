#pragma once

#ifdef D_BSN_msg_parser_IS_DLL
	#define D_BSN_msg_parser_DLL D_DllExport
#else
	#define D_BSN_msg_parser_DLL D_DllImport
	#ifdef _DEBUG
		#pragma comment(lib, "lib_bsn_msg_parser_d.lib")
	#else
		#pragma comment(lib, "lib_bsn_msg_parser.lib")
	#endif
#endif


