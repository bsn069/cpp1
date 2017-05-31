#pragma once

#include <bsn/include/port.h>
#include <bsn/common/include/lib_def.h>

D_BsnNamespace2(Common,OS)
 
enum E_OSType
{
	EOSType_Unknown = 0,

	EOSType_WinXP,
	EOSType_WinVista,
	EOSType_Win7,

	EOSTypes,
};


D_FunDef D_BSN_common_DLL E_OSType D_const Type( );
D_FunDef D_BSN_common_DLL T_wchar D_const * D_const Type2Wstr(E_OSType D_const e_OSType);

D_FunDef D_BSN_common_DLL T_void	Memory(T_uint32& u32_Total, T_uint32& u32_Free, T_uint32& u32_Used, T_uint32& u32_Peak);
 
	

D_BsnNamespace2End
 