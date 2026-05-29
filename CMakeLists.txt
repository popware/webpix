cmake_minimum_required(VERSION 3.18.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project( webpix )
add_executable( ${PROJECT_NAME} webpix.cpp )

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} /usr/include/X11 )

set(X11)
link_directories( /usr/lib/X11 )
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} X11 )
