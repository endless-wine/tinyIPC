SET(PROJ_NAME main)

file(GLOB CPP_SOURCE_FILE "*.cpp")

set(ALL_SOURCES ${CPP_SOURCE_FILE} ${C_SOURCE_FILE})

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${PROJECT_SOURCE_DIR}/device/panda/3516cv500/mpp/lib/)

if(CHIP_ID STREQUAL "dv300")
    link_libraries(common utils hdmi hi_cipher svpruntime _hidehaze _hidrc _hildci hi_cipher _hiawb_natura dnvqe nnie upvqe isp ive VoiceEngine sns_imx307_2l sns_imx307 sns_imx327_2l sns_imx327 sns_imx335 sns_imx377 sns_imx458 sns_mn34220 sns_os05a_2l sns_os05a _hiae _hiawb _hiawb_natura md upvqe hive_common hive_HPF hive_EQ hive_ANR hive_AGC hive_AEC aaccomm aacdec aacenc dnvqe securec ive mpi tde pthread rt)
elseif(CHIP_ID STREQUAL "m64x86")
    link_libraries(pthread rt common utils)
endif()

add_executable(${PROJ_NAME} ${ALL_SOURCES})

