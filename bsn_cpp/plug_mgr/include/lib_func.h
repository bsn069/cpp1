#pragma once

#include "i_plug_mgr.h"

#include <bsn_cpp/include/define.h>
#include <bsn_cpp/include/name_space.h>

D_BsnNamespace1(plug_mgr)
D_DllImport I_PlugMgr::T_SPI_PlugMgr NewPlugMgr();
D_BsnNamespace1End
