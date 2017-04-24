cmake_minimum_required(VERSION 3.7.0)

project(qt_pgrcam)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if(MSVC)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.8\\msvc2015_64\\")
endif()
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

find_package(FlyCapture2 REQUIRED)

file(GLOB cpp "*.cpp")
file(GLOB h "*.h" "*.hpp")
file(GLOB ui "*.ui")
add_executable(${PROJECT_NAME} ${cpp} ${h} ${ui})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Multimedia)

include_directories(${FLYCAPTURE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${FLYCAPTURE_LIBRARIES})

if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()
