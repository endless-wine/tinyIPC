SET(PROJ_NAME main)

include_directories(${PROJECT_SOURCE_DIR}/third_party/json/include/ ${PROJECT_SOURCE_DIR}/third_party/spdlog/include/ ${PROJECT_SOURCE_DIR}/third_party/googletest/googletest/include/
                    ${PROJECT_SOURCE_DIR}/drivers/interfaces/)

file(GLOB CPP_SOURCE_FILE "*.cpp")

set(ALL_SOURCES ${CPP_SOURCE_FILE} ${C_SOURCE_FILE})

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${PROJECT_SOURCE_DIR}/device/panda/3516cv500/mpp/lib/)

link_libraries(platform hdmi hi_cipher svpruntime _hidehaze _hidrc _hildci hi_cipher _hiawb_natura dnvqe nnie upvqe isp ive VoiceEngine sns_imx307_2l sns_imx307 sns_imx327_2l sns_imx327 sns_imx335 sns_imx377 sns_imx458 sns_mn34220 sns_os05a_2l sns_os05a _hiae _hiawb _hiawb_natura md upvqe hive_common hive_HPF hive_EQ hive_ANR hive_AGC hive_AEC aaccomm aacdec aacenc dnvqe securec ive mpi tde pthread rt gtest)

add_executable(${PROJ_NAME} ${ALL_SOURCES})

