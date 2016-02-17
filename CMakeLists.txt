cmake_minimum_required(VERSION 2.8)

project( vo )

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )

find_package( OpenCV REQUIRED )

set( VO_INCLUDE_DIRS include )
file(GLOB VO_FILES "src/*.cpp")

set( DEMO_INCLUDE_DIRS demo )

include_directories( ${OpenCV_INCLUDE_DIRS} ${VO_INCLUDE_DIRS} ${DEMO_INCLUDE_DIRS} )

add_executable( visodo demo/visodo.cpp )

add_library( vo SHARED ${VO_FILES} )  

target_link_libraries( visodo vo )
target_link_libraries( vo ${OpenCV_LIBS} )
