#pragma once
#include <bsn_cpp/include/define.h>

D_BsnNamespace1(lib_loader)
D_FunDef D_BSN_lib_loader_DLL I_Interface*	Create();
D_FunDef D_BSN_lib_loader_DLL void			Release(I_Interface* pInterface);
D_BsnNamespace1End
