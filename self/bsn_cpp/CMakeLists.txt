FILE(GLOB V_SelfPath "CMakeLists.txt")
MESSAGE(STATUS "工程名设置文件 " ${V_SelfPath})
STRING( REGEX REPLACE ".*/(.*)/CMakeLists.txt$" "\\1" V_prjName ${V_SelfPath} )
 

# 工程名 
PROJECT( ${V_prjName} ) 
MESSAGE(STATUS "------------------------------------------------------------- ")
MESSAGE(STATUS "工程名 " ${PROJECT_NAME})
MESSAGE(STATUS "工程PROJECT_BINARY_DIR " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "工程PROJECT_SOURCE_DIR " ${PROJECT_SOURCE_DIR})
# 最低需求cmake版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


# 二进制文件存放位置
SET(EXECUTABLE_OUTPUT_PATH $ENV{bsn_out})
MESSAGE(STATUS "二进制文件存放位置 " ${EXECUTABLE_OUTPUT_PATH})
# LIB文件存放位置
SET(LIBRARY_OUTPUT_PATH $ENV{bsn_out})
MESSAGE(STATUS "LIB文件存放位置 " ${LIBRARY_OUTPUT_PATH})

# 设置变量 表示本目录
SET(ROOT_DIR ${PROJECT_SOURCE_DIR})
# 设置变量 debug 后缀
SET( CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "add a postfix, usually d on windows" )

# 搜索路径
INCLUDE_DIRECTORIES( $ENV{bsn_dir} )
INCLUDE_DIRECTORIES( $ENV{bsn_lib3_include} )
LINK_DIRECTORIES( ${LIBRARY_OUTPUT_PATH} )
LINK_DIRECTORIES( $ENV{bsn_lib3_lib} )
# 添加定义
add_definitions(-DUNICODE -D_UNICODE)
#-------------------------------------------------------------------------------
 
# 添加子工程目录
ADD_SUBDIRECTORY( template_console )
ADD_SUBDIRECTORY( template_share_lib )

ADD_SUBDIRECTORY( common )
ADD_SUBDIRECTORY( dynamic_lib )
ADD_SUBDIRECTORY( log )
ADD_SUBDIRECTORY( console_input )

ADD_SUBDIRECTORY( loader )
ADD_SUBDIRECTORY( global )
ADD_SUBDIRECTORY( service_template )
ADD_SUBDIRECTORY( service_tcp_client )
ADD_SUBDIRECTORY( service_tcp_server )

#ADD_SUBDIRECTORY( udp )
ADD_SUBDIRECTORY( tcp )
ADD_SUBDIRECTORY( msg_parser )
#ADD_SUBDIRECTORY( udp_t )

#ADD_SUBDIRECTORY( BSNNet )
#ADD_SUBDIRECTORY( BSNNetTest )
#ADD_SUBDIRECTORY( BSNNet_TestC )
#ADD_SUBDIRECTORY( BSNNet_TestS )

#ADD_SUBDIRECTORY( BSNGate )

# ADD_SUBDIRECTORY( nodedll )
# ADD_SUBDIRECTORY( CheckCode )

# ADD_SUBDIRECTORY( BSNMysql )
# ADD_SUBDIRECTORY( BSNMysql_Test )

# ADD_SUBDIRECTORY( volumedll )
# ADD_SUBDIRECTORY( VolumeDllT )
#ADD_SUBDIRECTORY( BSNConsole )



MESSAGE(STATUS "------------------------------------------------------------- ")


# 依赖子项目
# ADD_DEPENDENCIES( BSN )
# 依赖第三方库
# TARGET_LINK_LIBRARIES(mysqlcppconn )
