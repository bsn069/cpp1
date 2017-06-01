cmake_minimum_required(VERSION 2.8)
project(cpp1)

# get CWD
execute_process(
  COMMAND pwd
  OUTPUT_VARIABLE _PWD
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(_PWD= ${_PWD})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out)

message(PROJECT_SOURCE_DIR= ${PROJECT_SOURCE_DIR})
message(EXECUTABLE_OUTPUT_PATH= ${EXECUTABLE_OUTPUT_PATH})
message(LIBRARY_OUTPUT_PATH= ${LIBRARY_OUTPUT_PATH})
message(CMAKE_BUILD_TYPE= ${CMAKE_BUILD_TYPE})

# -g选项，产生供gdb调试用的可执行文件 2(扩展的符号表、行号、局部或外部变量信息) 3(2及源代码中定义的宏)
# -Wall选项意思是编译后显示所有警告
# -f后面跟一些编译选项
# 	PIC是其中一种，表示生成位置无关代码（Position Independent Code）位置无关码就是可以在进程的任意内存位置执行的目标码，动态链接库必须使用
#	exceptions 参数编译出正确处理异常的代码 Enable exception handling
set(MY_COMMON_FLAG    "-g3 -fexceptions -Wall -fPIC -DOS_LINUX -D__STDC_FORMAT_MACROS")
set(MY_C_DEBUG_FLAG   "${MY_COMMON_FLAG} -O0 -D_DEBUG -DCHECK_MEM_LEAK")
# -O2选项，最大优化
set(MY_C_RELEASE_FLAG "${MY_COMMON_FLAG} -O2 -DNDEBUG")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(MY_C_FLAGS   "${MY_C_DEBUG_FLAG}")
  set(OUTPUT_SUFFIX "d")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(MY_C_FLAGS   "${MY_C_RELEASE_FLAG}")
  set(OUTPUT_SUFFIX "")
endif()

set(CMAKE_CXX_FLAGS "${MY_C_FLAGS} -std=gnu++11" CACHE INTERNAL "global cxx flags")
set(CMAKE_C_FLAGS   "${MY_C_FLAGS}"              CACHE INTERNAL "global c flags")
message(CMAKE_CXX_FLAGS= ${CMAKE_CXX_FLAGS})
message(CMAKE_C_FLAGS= ${CMAKE_C_FLAGS})
message(OUTPUT_SUFFIX= ${OUTPUT_SUFFIX})

add_subdirectory(test)

