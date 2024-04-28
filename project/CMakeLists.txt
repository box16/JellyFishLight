add_executable(jellyfishlight)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)

pico_generate_pio_header(jellyfishlight ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_sources(jellyfishlight PRIVATE main.cpp)
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/LightingSystem)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Pixel)
include_directories(${CMAKE_CURRENT_LIST_DIR}/LightingPattern)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Switch)
include_directories(${CMAKE_CURRENT_LIST_DIR}/RGB)

target_link_libraries(jellyfishlight PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(jellyfishlight)

# Additionally generate python and hex pioasm outputs for inclusion in the RP2040 datasheet
add_custom_target(pio_ws2812_datasheet DEPENDS ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py)
add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio
        COMMAND Pioasm -o python ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py
        VERBATIM)
add_dependencies(jellyfishlight pio_ws2812_datasheet)