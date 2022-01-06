cmake_minimum_required(VERSION 3.19)

project(sfml_game VERSION 1.0.0)

add_executable(app main.cpp)

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