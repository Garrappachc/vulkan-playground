cmake_minimum_required (VERSION 3.10 FATAL_ERROR)
project (vulkan-intro)

find_package (Vulkan REQUIRED)
find_package (glm REQUIRED)

find_package (PkgConfig REQUIRED)
pkg_search_module (GLFW REQUIRED glfw3)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable (intro
    application.h
    application.cpp
    main.cpp
)

configure_file (config.h.in config.h)
target_sources (intro PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/config.h)

set (intro_SHADERS
    shader.frag
    shader.vert
)

set (intro_SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

find_program (glslangValidator glslangValidator)

foreach (shader ${intro_SHADERS})
    add_custom_command (OUTPUT ${shader}.spv
        DEPENDS ${intro_SHADERS_DIR}/${shader}
        COMMAND ${glslangValidator}
        ARGS -V ${intro_SHADERS_DIR}/${shader} -o ${shader}.spv
        VERBATIM
    )
endforeach ()

add_custom_target (compile_shaders ALL
    DEPENDS
        shader.frag.spv
        shader.vert.spv
)

target_include_directories (intro PRIVATE
    ${CMAKE_SOURCE_DIR}/3rdparty
    ${GLFW_INCLUDE_DIRS}
)
target_link_libraries (intro PUBLIC
    ${GLFW_LIBRARIES}
    Vulkan::Vulkan
)
