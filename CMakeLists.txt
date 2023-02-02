cmake_minimum_required(VERSION 3.17)
include(FetchContent)

project(wallpaper_creator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED, True)

file(GLOB_RECURSE SOURCES "./src/*.cpp")

FetchContent(
    opencv
    GIT_REPOSITORY https://github.com/opencv/opencv.git
    GIT_TAG 4.7.0
)

FetchContent_MakeAvailable(opencv)

find_package(X11 REQUIRED)
find_package(OpenCV REQUIRED)
# find_package(Imlib2 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES} "./main.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${X11_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC ${X11_LIBRARIES}
                                            ${OpenCV_LIBS}
                                            Imlib2
                                            Xrandr
                                            pthread
                                            )
