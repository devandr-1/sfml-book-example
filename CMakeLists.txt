cmake_minimum_required(VERSION 3.19)

project(sfml_game VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES *.h, *.cpp)

add_executable(app main.cpp ${SOURCES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(app OpenGL::GL)

if(APPLE)
    set(SFML_PATH $ENV{HOME}/Projects/lib/SFML-2.5.1)

    target_include_directories(app PUBLIC ${SFML_PATH}/include)
    
    target_link_libraries(app ${SFML_PATH}/lib/libsfml-graphics.2.5.1.dylib)
    target_link_libraries(app ${SFML_PATH}/lib/libsfml-network.2.5.1.dylib)
    target_link_libraries(app ${SFML_PATH}/lib/libsfml-system.2.5.1.dylib)
    target_link_libraries(app ${SFML_PATH}/lib/libsfml-window.2.5.1.dylib)
    target_link_libraries(app ${SFML_PATH}/lib/libsfml-audio.2.5.1.dylib)

    target_link_libraries(app "-framework Cocoa -framework IOKit")
endif()

if (WIN32)
    set(SFML_PATH D:\\Projects\\repos\\lib\\SFML-2.5.1)

    target_include_directories(app PUBLIC ${SFML_PATH}\\include)

    target_link_libraries(app ${SFML_PATH}\\lib\\sfml-main-d.lib)
    target_link_libraries(app ${SFML_PATH}\\lib\\sfml-graphics-d.lib)
    target_link_libraries(app ${SFML_PATH}\\lib\\sfml-network-d.lib)
    target_link_libraries(app ${SFML_PATH}\\lib\\sfml-system-d.lib)
    target_link_libraries(app ${SFML_PATH}\\lib\\sfml-window-d.lib)
    target_link_libraries(app ${SFML_PATH}\\lib\\sfml-audio-d.lib)
endif()