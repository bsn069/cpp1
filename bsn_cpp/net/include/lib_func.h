#pragma once

#include "i_net.h"

#include <bsn_cpp/load_lib/include/i_lib.h>
#include <bsn_cpp/include/define.h>

#include <boost/asio.hpp>

D_BsnNamespace1(net)
// D_FunDef D_DllCImport I_Net::T_SPI_Net	
// NewNet(D_N1(load_lib)::I_Lib::T_SPI_Lib, boost::asio::io_service&);

typedef I_Net::T_SPI_Net	(*T_NewNet)(D_N1(load_lib)::I_Lib::T_SPI_Lib, boost::asio::io_service&);
D_BsnNamespace1End
