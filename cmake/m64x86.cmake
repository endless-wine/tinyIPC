set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_C_COMPILER   gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_FIND_ROOT_PATH  gnueabihf)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -fPIC -Wall -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb -fPIC -Wall -Wextra")

string(TOLOWER ${CMAKE_SYSTEM_NAME} CW_SYSTEM_NAME)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/m64x86/lib)  	#静态库路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/m64x86/lib)  	#动态库路径	
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/m64x86/bin) 	#可执行文件路径
set(CMAKE_PDB_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/m64x86/elf)	#符号文件
