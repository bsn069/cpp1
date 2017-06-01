#pragma once
#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/name_space.h>

D_BsnNamespace1(NameSpace)
D_FunDef D_BSN_t_share_DLL I_Interface*	Create();
D_FunDef D_BSN_t_share_DLL void		Release(I_Interface* pInterface);
D_BsnNamespace1End
