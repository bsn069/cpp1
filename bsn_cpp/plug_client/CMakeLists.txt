FILE(GLOB V_SelfPath "CMakeLists.txt")
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
add_definitions( -D${LIB_DEFINE_PREFIX}${PROJECT_NAME})
add_definitions( -DD_OutInfoOpen)

# 生成lib
SET( OUT_NAME ${LIB_PREFIX_D}${PROJECT_NAME}${OUTPUT_SUFFIX} )
ADD_LIBRARY(${OUT_NAME} SHARED ${SRC_LIST})
#SET_TARGET_PROPERTIES(${OUT_NAME} PROPERTIES DEBUG_POSTFIX "${OUTPUT_SUFFIX}")
# 依赖项目
#target_link_libraries(${OUT_NAME} ${LIB_PREFIX_D}common${OUTPUT_SUFFIX})
# 链接库
#target_link_libraries(${OUT_NAME} bsn_nedmalloc)
#target_link_libraries(${OUT_NAME} ssl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -rdynamic")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -fPIC -rdynamic")

MESSAGE(STATUS "")
MESSAGE(STATUS "------------------------------------------------------------- ")
MESSAGE(STATUS "工程名 " ${PROJECT_NAME})
MESSAGE(STATUS "工程cmake文件 " ${V_SelfPath})
MESSAGE(STATUS "工程PROJECT_BINARY_DIR " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "工程PROJECT_SOURCE_DIR " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "CMAKE_C_FLAGS " ${CMAKE_C_FLAGS})
MESSAGE(STATUS "CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS})
MESSAGE(STATUS "OUT_NAME " ${OUT_NAME})
MESSAGE(STATUS "源码列表 ")
FOREACH(src ${SRC_LIST})
MESSAGE( ${src} )
ENDFOREACH()

