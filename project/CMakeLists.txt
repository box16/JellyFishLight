add_executable(jellyfishlight)

target_sources(jellyfishlight PRIVATE main.cpp)
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/ProgrammableLED)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Switch)

target_link_libraries(jellyfishlight PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(jellyfishlight)

set(PIO_TARGET jellyfishlight)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/ProgrammableLED/WS2812B)