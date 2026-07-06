cmake_minimum_required(VERSION 3.31)
project(playground
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -gdwarf-4 -DDEBUG -fsanitize=address -fno-omit-frame-pointer")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Default Build Type : Release" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_library(common_config INTERFACE)
target_compile_options(common_config INTERFACE -Wall -Wpedantic -Wextra)
# target_compile_options(common_config INTERFACE -Wall -Wpedantic -Wextra -freflection)
target_link_libraries(common_config INTERFACE)
# target_link_libraries(common_config INTERFACE -lpqxx -lpq)

file(GLOB SOURCE_FILES src/*.c src/*.cpp)

foreach(SOURCE_PATH ${SOURCE_FILES})
    get_filename_component(APP_NAME ${SOURCE_PATH} NAME_WLE)
    add_executable(${APP_NAME} ${SOURCE_PATH})
    target_include_directories(${APP_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)
    target_link_libraries(
        ${APP_NAME} PRIVATE
        common_config
    )
    set_target_properties(
        ${APP_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin"
        INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
        INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE
        CXX_STANDARD 26
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF
    )
endforeach()

