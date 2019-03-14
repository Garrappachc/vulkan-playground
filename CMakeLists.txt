cmake_minimum_required (VERSION 3.10 FATAL_ERROR)
project (vulkan-playground)

find_package (Vulkan REQUIRED)
find_package (glm REQUIRED)

find_package (PkgConfig REQUIRED)
pkg_search_module (GLFW REQUIRED glfw3)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_CXX_FLAGS_DEBUG "-g -ggdb -Wall -Wextra -Wpedantic")

add_subdirectory (3rdparty)

add_executable (playground
    application.h
    application.cpp
    fpscounter.h
    fpscounter.cpp
    object.h
    object.cpp
    scene.h
    scene.cpp

    main.cpp

    $<TARGET_OBJECTS:imgui>
)

configure_file (config.h.in config.h)
target_sources (playground PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/config.h)

set (playground_SHADERS
    shader.frag
    shader.vert
)

set (playground_SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

find_program (glslangValidator glslangValidator)

foreach (shader ${playground_SHADERS})
    add_custom_command (OUTPUT ${shader}.spv
        DEPENDS ${playground_SHADERS_DIR}/${shader}
        COMMAND ${glslangValidator}
        ARGS -V ${playground_SHADERS_DIR}/${shader} -o ${shader}.spv
        VERBATIM
    )
endforeach ()

add_custom_target (compile_shaders ALL
    DEPENDS
        shader.frag.spv
        shader.vert.spv
)

target_include_directories (playground PRIVATE
    ${CMAKE_SOURCE_DIR}/3rdparty
    ${GLFW_INCLUDE_DIRS}
)
target_link_libraries (playground PUBLIC
    ${GLFW_LIBRARIES}
    Vulkan::Vulkan
)
