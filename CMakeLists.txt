cmake_minimum_required(VERSION 2.8)
project(server)
#set(PRODUCTS_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../../../swordm3d-products/trunk/server)

message(${PROJECT_SOURCE_DIR})
message(${EXECUTABLE_OUTPUT_PATH})
message(${LIBRARY_OUTPUT_PATH})
message(${RELEASEFLAG})
message(${PLATFLAG})
message(${CMAKE_BUILD_TYPE})
message(${OUTPUT_SUFFIX})
message(${CMAKE_CXX_FLAGS})
message(${CMAKE_C_FLAGS})
 
# get CWD
execute_process(
  COMMAND pwd
  OUTPUT_VARIABLE _PWD
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(${CWD})
cmake_print_variables(_PWD BASE_SOURCE_DIR)
