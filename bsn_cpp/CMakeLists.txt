# 查找自己所在目录名
#-------------------------------------------------------------------------------
FILE(GLOB V_SelfPath "CMakeLists.txt")
STRING( REGEX REPLACE ".*/(.*)/CMakeLists.txt$" "\\1" V_prjName ${V_SelfPath} )
#-------------------------------------------------------------------------------


# 工程信息 
#-------------------------------------------------------------------------------
PROJECT( ${V_prjName} ) 
MESSAGE(STATUS "")
MESSAGE(STATUS "------------------------------------------------------------- ")
MESSAGE(STATUS "CMAKE_BUILD_TYPE " ${CMAKE_BUILD_TYPE})
MESSAGE(STATUS "工程名 " ${PROJECT_NAME})
MESSAGE(STATUS "工程cmake文件 " ${V_SelfPath})
MESSAGE(STATUS "工程PROJECT_BINARY_DIR " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "工程PROJECT_SOURCE_DIR " ${PROJECT_SOURCE_DIR})
# 最低需求cmake版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
#-------------------------------------------------------------------------------


# 生成位置
#-------------------------------------------------------------------------------
# 二进制文件存放位置
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)
MESSAGE(STATUS "二进制文件存放位置 " ${EXECUTABLE_OUTPUT_PATH})
# LIB文件存放位置
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)
MESSAGE(STATUS "LIB文件存放位置 " ${LIBRARY_OUTPUT_PATH})
#-------------------------------------------------------------------------------


# 变量
#-------------------------------------------------------------------------------
# 设置变量 表示本目录
SET(ROOT_DIR ${PROJECT_SOURCE_DIR})
# 动态库前缀
SET(LIB_PREFIX_D bsn_dlib_)
# 静态库前缀
SET(LIB_PREFIX_S bsn_slib_)
# 可执行文件前缀
SET(BIN_PREFIX bsn_2_)
# 库定义前缀
SET(LIB_DEFINE_PREFIX D_BSN_IS_DLL_)

# 头文件路径
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/../ )
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/third_part/boost )


# 链接库查找目录
LINK_DIRECTORIES( ${LIBRARY_OUTPUT_PATH} )

# 添加定义
add_definitions(-DUNICODE -D_UNICODE)
add_definitions(-DBOOST_COROUTINES_NO_DEPRECATION_WARNING)
#-------------------------------------------------------------------------------


# 编译选项
#-------------------------------------------------------------------------------
# -g选项，产生供gdb调试用的可执行文件 2(扩展的符号表、行号、局部或外部变量信息) 3(2及源代码中定义的宏)
# -Wall选项意思是编译后显示所有警告
# -f后面跟一些编译选项
# 	PIC是其中一种，表示生成位置无关代码（Position Independent Code）位置无关码就是可以在进程的任意内存位置执行的目标码，动态链接库必须使用
#	exceptions 参数编译出正确处理异常的代码 Enable exception handling
set(MY_COMMON_FLAG    "-g3 -fexceptions -Wall -DOS_LINUX -D__STDC_FORMAT_MACROS -pthread")
set(MY_C_DEBUG_FLAG   "${MY_COMMON_FLAG} -O0 -D_DEBUG -DCHECK_MEM_LEAK")
# -O2选项，最大优化
set(MY_C_RELEASE_FLAG "${MY_COMMON_FLAG} -O2 -DNDEBUG")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(MY_C_FLAGS   "${MY_C_DEBUG_FLAG}")
  set(OUTPUT_SUFFIX "_d")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(MY_C_FLAGS   "${MY_C_RELEASE_FLAG}")
  set(OUTPUT_SUFFIX "")
endif()

set(CMAKE_CXX_FLAGS "${MY_C_FLAGS} -std=gnu++11" CACHE INTERNAL "global cxx flags")
set(CMAKE_C_FLAGS   "${MY_C_FLAGS}"              CACHE INTERNAL "global c flags")
MESSAGE(STATUS "CMAKE_C_FLAGS " ${CMAKE_C_FLAGS})
MESSAGE(STATUS "CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS})
MESSAGE(STATUS "OUTPUT_SUFFIX " ${OUTPUT_SUFFIX})
#-------------------------------------------------------------------------------

 
# 添加子工程目录
#-------------------------------------------------------------------------------
# ADD_SUBDIRECTORY( test )
# ADD_SUBDIRECTORY( t_console )
# ADD_SUBDIRECTORY( t_share )
# ADD_SUBDIRECTORY( lib_loader )
# ADD_SUBDIRECTORY( log )
# ADD_SUBDIRECTORY( console_input )
# ADD_SUBDIRECTORY( global )
# ADD_SUBDIRECTORY( common )
# ADD_SUBDIRECTORY( net )
# ADD_SUBDIRECTORY( load_lib )
# ADD_SUBDIRECTORY( log )
# ADD_SUBDIRECTORY( sqlite )
# ADD_SUBDIRECTORY( loader )
# ADD_SUBDIRECTORY( global )
# ADD_SUBDIRECTORY( input )
ADD_SUBDIRECTORY( plug_mgr_loader )
ADD_SUBDIRECTORY( plug_mgr )
#ADD_SUBDIRECTORY( plug_one )
ADD_SUBDIRECTORY( plug_cmd )
ADD_SUBDIRECTORY( plug_net )
#ADD_SUBDIRECTORY( plug_log )
#-------------------------------------------------------------------------------

MESSAGE(STATUS "------------------------------------------------------------- ")