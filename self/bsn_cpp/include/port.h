#pragma once

#if (defined _MSC_VER)
# pragma warning( push )
# pragma warning( disable : 4819 ) 
# pragma warning( disable : 4996 )
# pragma warning( disable : 4244 )
#endif
#define _WIN32_WINNT 0x0501

#include <bsn/include/std.h>
#include <bsn/include/boost.h>

#include <bsn/include/base_type.h>
#include <bsn/include/name_space.h>
#include <bsn/include/const.h>
#include <bsn/include/define.h>

#include <bsn/include/malloc.hpp>
#include <bsn/include/free.hpp>
#include <bsn/include/new.hpp>
#include <bsn/include/delete.hpp>
#include <bsn/include/new_array.hpp>
#include <bsn/include/delete_array.hpp>
#include <bsn/include/new_tools.hpp>
#include <bsn/include/delete_tools.hpp>

#include <bsn/include/utils.hpp>
#include <bsn/include/bit.hpp>

#include <bsn/include/fsm.hpp>
#include <bsn/include/double_list.hpp>
#include <bsn/include/string.hpp>
#include <bsn/include/singleton.hpp>
#include <bsn/include/msg_header.hpp>
#include <bsn/include/buffer.hpp>

#if (defined _MSC_VER)
# pragma warning( pop )
#endif


