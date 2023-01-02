include_directories(./include)
aux_source_directory(./src/ COMMON_SRCS)
add_library(common STATIC ${COMMON_SRCS})