cmake_minimum_required(VERSION 2.8.3)
project(map_ed_qt)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

##   rosros
find_package(catkin REQUIRED COMPONENTS
        nav_msgs
        roscpp
        rospy
        qt_build
        sensor_msgs
        std_msgs
        tf
        rviz
        visualization_msgs
        )



set(QT_USE_QTOPENGL TRUE)
find_package(OpenCV REQUIRED)
find_package(Qt5 ${rviz_QT_VERSION} EXACT REQUIRED Core Widgets)

## ros
include_directories(
        ${Boost_INCLUDE_DIR}
        ${catkin_INCLUDE_DIRS})

include_directories( ${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${QT_QTOPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} )
include_directories(${Qt5Widgets_INCLUDE_DIRS}  )

#ros
catkin_package(CATKIN_DEPENDS ${${PROJECT_NAME}_CATKIN_DEPS})


link_directories(${OpenCV_LIBRARY_DIRS})


find_package(Qt5Network REQUIRED)

set(QT_INCLUDE_DIRS ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS})
set(QT_LIBRARIES Qt5::Gui Qt5::Widgets Qt5::Network)
add_definitions(${Qt5Gui_DEFINITIONS} ${Qt5Widgets_DEFINITIONS} ${Qt5Network_DEFINITIONS})



file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/map_editor/*.hpp include/map_editor/*.h)
###########
## Build ##
###########
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5XmlPatterns REQUIRED)
find_package(OpenGL REQUIRED )

#绝对路径需要修改
include_directories(include/map_editor ui/ include/GpsImu7661 )
#

if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)




set(SOURCE_FILES src/ include/map_editor/ )

add_executable(map_ed_qt ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP} )
target_link_libraries(map_ed_qt ${QT_LIBRARIES} ${OpenCV_LIBS}   ${catkin_LIBRARIES} )

set_target_properties(map_ed_qt
        PROPERTIES COMPILE_FLAGS "-fPIC"
        )
qt5_use_modules(map_ed_qt Core Widgets Gui PrintSupport Sql Xml XmlPatterns)

#install(TARGETS map_ed_qt RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


#install(TARGETS map_ed_qt RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}) # RUNTIME DESTINATION
