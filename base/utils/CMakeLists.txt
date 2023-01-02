include_directories(./include/utils)
aux_source_directory(./src/ COMMON_SRCS)
add_library(utils STATIC ${COMMON_SRCS})