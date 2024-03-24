cmake_minimum_required(VERSION 3.7)

project(course_work
    VERSION 0.0.0
    DESCRIPTION "Qt integration with VulkanSceneGraph"
    LANGUAGES CXX
)

# set the use of C++17 globally as all examples require it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_PACKAGE_NAME Qt5 CACHE STRING "Set Qt package name, i.e. Qt5 or Qt6.")

# if Qt5 then we need 5.10 or later
find_package(${QT_PACKAGE_NAME} COMPONENTS Core Widgets PrintSupport REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
    main.cpp
    calculatethread.cpp
    mainwindow.cpp
    qcustomplot.cpp
)

set(HEADERS
    calculatethread.h
    qcustomplot.h
    mainwindow.h
)

set(FORMS
    mainwindow.ui
)

add_executable(course_work ${MODE} ${SOURCES} ${HEADERS} ${FORMS})

target_include_directories(course_work PRIVATE .)

target_link_libraries(course_work ${QT_PACKAGE_NAME}::Widgets ${QT_PACKAGE_NAME}::PrintSupport)
