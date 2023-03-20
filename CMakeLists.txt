cmake_minimum_required(VERSION 3.16)

project(PointSize_Qt6_Quick3D VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED Quick3D)

qt_add_executable(appPointSize_Qt6_Quick3D
    main.cpp
    pointcloudcubegeometry.h
    pointcloudcubegeometry.cpp
)

qt_add_qml_module(appPointSize_Qt6_Quick3D
    URI PointSize_Qt6_Quick3D
    VERSION 1.0
    QML_FILES
        main.qml
)

set_target_properties(appPointSize_Qt6_Quick3D PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPointSize_Qt6_Quick3D
    PRIVATE Qt6::Quick
    Qt6::Quick3D
)

install(TARGETS appPointSize_Qt6_Quick3D
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
