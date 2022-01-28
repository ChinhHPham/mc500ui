cmake_minimum_required(VERSION 3.14)

project(CommManager LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)
find_package(Protobuf REQUIRED)

add_library(CommManager STATIC
  commmanager.cpp
  protoparser.cpp
  dataclasses.cpp
  tcpsocket.cpp

  commmanager.h
  protoparser.h
  dataclasses.h
  tcpsocket.h
)

target_link_libraries(CommManager PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network ${PROTOBUF_LIBRARIES})
target_link_libraries(CommManager LINK_PUBLIC protos)

target_compile_definitions(CommManager PRIVATE COMMMANAGER_LIBRARY)

target_include_directories(CommManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Protos)
