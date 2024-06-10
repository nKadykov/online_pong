cmake_minimum_required(VERSION 3.10)
project(online_pong)

set(CMAKE_CXX_STANDART 23)
set(CMAKE_CXX_STANDART_REQUIRED True)

set(ASSETS_FOLDER ${CMAKE_SOURCE_DIR}/assets)
set(ASSETS_OUTPUT_DIR Release/assets)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

include_directories(include)
set(SOURCES include/game.h include/paddle.h src/main.cpp src/game.cpp src/paddle.cpp)

find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics network audio)
find_package(Boost REQUIRED COMPONENTS system)

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_FOLDER} ${ASSETS_OUTPUT_DIR}
    COMMENT "Copying assets to output directory"
)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE YES LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio Boost::system)