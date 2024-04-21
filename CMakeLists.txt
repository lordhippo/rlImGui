cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(rlImGui)

include(GNUInstallDirs)

find_package(raylib CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

set (INSTALLABLE_HEADERS
	"rlImGui.h"
	"rlImGuiColors.h")

set(SOURCE_FILES
	"rlImGui.cpp")

set (INSTALLABLE_DOCFILES
  README.md
  LICENSE
)

SET(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Output directory for libraries")
SET(CMAKE_INSTALL_BINDIR bin CACHE PATH "Output directory for binaries")
SET(CMAKE_INSTALL_INCLUDEDIR include CACHE PATH "Output directory for header files")
SET(CMAKE_INSTALL_DOCDIR share/doc CACHE PATH "Output directory for documentation and license files")

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC
	raylib
	imgui::imgui)

INSTALL(FILES ${INSTALLABLE_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/rlimgui)
INSTALL(FILES ${INSTALLABLE_DOCFILES} DESTINATION ${CMAKE_INSTALL_DOCDIR}/rlimgui)

INSTALL(TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}_targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

INSTALL(EXPORT ${PROJECT_NAME}_targets
		FILE ${PROJECT_NAME}-targets.cmake
		NAMESPACE ${PROJECT_NAME}::
		DESTINATION share/${PROJECT_NAME}
)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
"include(CMakeFindDependencyMacro)\n"
"find_dependency(raylib)\n"
"find_dependency(imgui)\n"
"include(\"\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}-targets.cmake\")\n"
)

INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        DESTINATION share/${PROJECT_NAME})

OPTION(BUILD_EXAMPLE "Build the examples" OFF)

if (${BUILD_EXAMPLE})
    add_executable(${PROJECT_NAME}-example-simple "examples/simple.cpp")
	add_executable(${PROJECT_NAME}-example-imgui_style "examples/imgui_style_example.cpp")
	add_executable(${PROJECT_NAME}-example-editor "examples/editor.cpp")
               
    target_link_libraries(${PROJECT_NAME}-example-simple ${PROJECT_NAME})
	target_link_libraries(${PROJECT_NAME}-example-imgui_style ${PROJECT_NAME})
	target_link_libraries(${PROJECT_NAME}-example-editor ${PROJECT_NAME})
endif()
