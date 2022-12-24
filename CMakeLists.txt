cmake_minimum_required(VERSION 3.1)
project(endless)

if(CHIP_ID STREQUAL "m64x86")
    include(${CMAKE_SOURCE_DIR}/cmake/m64x86.cmake)
elseif(CHIP_ID STREQUAL "dv300")
    include(${CMAKE_SOURCE_DIR}/cmake/dv300.cmake)
endif()
message("chip id: ${CHIP_ID}")

include_directories(${PROJECT_SOURCE_DIR}/third_party/json/include/ ${PROJECT_SOURCE_DIR}/third_party/spdlog/include/ ${PROJECT_SOURCE_DIR}/third_party/googletest/googletest/include/
                    ${PROJECT_SOURCE_DIR}/drivers/interfaces/)

add_subdirectory(base)
add_subdirectory(foundation)
add_subdirectory(drivers)
#add_subdirectory(third_party)
add_subdirectory(applications)
