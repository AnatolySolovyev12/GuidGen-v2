cmake_minimum_required(VERSION 3.10)

project(GuidGen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)


set(SOURCES 
"${CMAKE_SOURCE_DIR}/source/GuidGenv2.cpp"
"${CMAKE_SOURCE_DIR}/source/main.cpp"
"${CMAKE_SOURCE_DIR}/source/GuidGenv2.h"
) # Добавьте сюда ваши файлы

qt6_wrap_ui(UI_HEADERS "${CMAKE_SOURCE_DIR}/source/GuidGenv2.ui")
qt6_add_resources(RESOURCES "${CMAKE_SOURCE_DIR}/source/GuidGenv2.qrc")
qt6_wrap_cpp(MOC_SOURCES ${SOURCES})

add_executable(MyApp ${SOURCES} ${MOC_SOURCES} ${UI_HEADERS} ${RESOURCES})

target_link_libraries(MyApp PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)