FILE(GLOB V_SelfPath "CMakeLists.txt")
MESSAGE(STATUS "工程名设置文件 " ${V_SelfPath})
STRING( REGEX REPLACE ".*/(.*)/CMakeLists.txt$" "\\1" V_prjName ${V_SelfPath} )
# 工程名 
PROJECT( ${V_prjName} ) 



# 加添src目录到的源码到变量SRC_LIST
# aux_source_directory(src  SRC_LIST)
FILE(GLOB_RECURSE SRC_LIST_CPP "*.cpp")
FILE(GLOB_RECURSE SRC_LIST_HPP "*.hpp")
FILE(GLOB_RECURSE SRC_LIST_C "*.c")
FILE(GLOB_RECURSE SRC_LIST_H "*.h")
set(SRC_LIST ${SRC_LIST_H} ${SRC_LIST_C} ${SRC_LIST_CPP} ${SRC_LIST_HPP})
  
# 头文件搜索路径 
#INCLUDE_DIRECTORIES( Include )
  
# 添加定义
add_definitions( -DD_BSN_${PROJECT_NAME}_IS_DLL )

# 生成lib
SET( OUT_NAME lib_bsn_${PROJECT_NAME} )
ADD_LIBRARY(${OUT_NAME} SHARED ${SRC_LIST})
SET_TARGET_PROPERTIES(${OUT_NAME} PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
# 依赖项目
target_link_libraries(${OUT_NAME} lib_bsn_common)
target_link_libraries(${OUT_NAME} lib_bsn_log)
target_link_libraries(${OUT_NAME} lib_bsn_dynamic_lib)
# target_link_libraries(${OUT_NAME} lib_bsn_service_test)
# 链接库
#target_link_libraries(${OUT_NAME} bsn_nedmalloc)

MESSAGE(STATUS "工程名 " ${PROJECT_NAME})
MESSAGE(STATUS "工程PROJECT_BINARY_DIR " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "工程PROJECT_SOURCE_DIR " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "源码列表 ")
FOREACH(src ${SRC_LIST})
MESSAGE( ${src} )
ENDFOREACH()

