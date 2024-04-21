cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(rlImGui)

find_package(raylib CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

file(GLOB_RECURSE GEN_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Source/*.c" "Source/*.cpp" "/Source/*.cc" "/Source/*.cxx")
file(GLOB_RECURSE GEN_HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "Source/*.h" "Source/*.hpp")

set(SOURCE_FILES
	"rlImGui.h"
	"rlImGui.cpp"
	"rlImGuiColors.h"
	"imgui_impl_raylib.h"
	"extras/FA6FreeSolidFontData.h"
	"extras/IconsFontAwesome6.h")

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC
	raylib
	imgui::imgui)

OPTION(BUILD_EXAMPLE "Build the examples" OFF)

if (${BUILD_EXAMPLE})
    add_executable(${PROJECT_NAME}-example-simple "examples/simple.cpp")
	add_executable(${PROJECT_NAME}-example-imgui_style "examples/imgui_style_example.cpp")
	add_executable(${PROJECT_NAME}-example-editor "examples/editor.cpp")
               
    target_link_libraries(${PROJECT_NAME}-example-simple ${PROJECT_NAME})
	target_link_libraries(${PROJECT_NAME}-example-imgui_style ${PROJECT_NAME})
	target_link_libraries(${PROJECT_NAME}-example-editor ${PROJECT_NAME})
endif()
