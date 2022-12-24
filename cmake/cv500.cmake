set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_C_COMPILER   arm-himix200-linux-gcc)
set(CMAKE_CXX_COMPILER arm-himix200-linux-g++)
set(CMAKE_FIND_ROOT_PATH  arm-himix200-linux-gnueabihf)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdata-sections -ffunction-sections -fstack-protector-all -frtti -fexceptions -Wno-psabi")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdata-sections -ffunction-sections -fstack-protector-all -fexceptions")

string(TOLOWER ${CMAKE_SYSTEM_NAME} CW_SYSTEM_NAME)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/dv300/lib)  	#静态库路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/dv300/lib)  	#动态库路径	
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/dv300/bin) 	#可执行文件路径
set(CMAKE_PDB_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/dv300/elf)	#符号文件	
