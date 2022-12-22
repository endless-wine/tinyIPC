SET(PROJ_NAME platform)

include_directories(${PROJECT_SOURCE_DIR}/third_party/json/include/ ${PROJECT_SOURCE_DIR}/third_party/spdlog/include/ ${PROJECT_SOURCE_DIR}/third_party/googletest/googletest/include/
${PROJECT_SOURCE_DIR}/device/panda/3516cv500/mpp/include/ ${PROJECT_SOURCE_DIR}/platform/include)

file(GLOB CPP_SOURCE_FILE "*.cpp" "*.c" "${PROJECT_SOURCE_DIR}/platform/src/media/common/*.c" "${PROJECT_SOURCE_DIR}/platform/src/media/test/*.cpp")

set(ALL_SOURCES ${CPP_SOURCE_FILE} ${C_SOURCE_FILE})

add_library(${PROJ_NAME} SHARED ${ALL_HDRS} ${ALL_SOURCES})

