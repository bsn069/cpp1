#pragma once


#ifdef D_BSN_service_template_IS_DLL
	#define D_BSN_service_template_DLL D_DllCExport
#else
	#define D_BSN_service_template_DLL D_DllCImport
	#ifdef _DEBUG
		#pragma comment(lib, "lib_bsn_service_template_d.lib")
	#else
		#pragma comment(lib, "lib_bsn_service_template.lib")
	#endif
#endif

