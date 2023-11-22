cmake_minimum_required(VERSION 3.5)
project(RtspServerExample)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
pkg_check_modules(GSTRTSPSERVER REQUIRED gstreamer-rtsp-server-1.0)

set(SOURCE_FILES rtsp_server.cpp)

add_executable(rtsp_server ${SOURCE_FILES})

target_include_directories(rtsp_server PRIVATE ${GSTREAMER_INCLUDE_DIRS} ${GSTRTSPSERVER_INCLUDE_DIRS})
target_link_libraries(rtsp_server PRIVATE ${GSTREAMER_LIBRARIES} ${GSTRTSPSERVER_LIBRARIES})

set_property(TARGET rtsp_server PROPERTY CXX_STANDARD 11)
