#pragma once
#include <bsn_cpp/include/define.h>
#include "i_interface.h"

D_BsnNamespace1(t_share)
D_FunDef D_DllCImport I_Interface::T_SharePtr	Create(I_Interface::T_SharePtrLibLoader libLoader);
D_BsnNamespace1End
