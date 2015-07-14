cmake_minimum_required(VERSION 2.8.10)
project(avVideo)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

find_package( avformat )
find_package( avcodec )
find_package( avutil )
find_package( swscale )
find_package( avdevice )

set(
    FFMPEG_LIBS
    avcodec
    avformat
    avdevice
    postproc
    avutil
    swresample
    swscale
)


include_directories(/usr/include/)
#include_directories(~/ffmpeg_source)
#link_directories(/usr/bin/)
link_directories(~/ffmpeg_source)
#link_directories(/usr/local/lib/)


include(CheckIncludeFiles)
check_include_files(libavcodec/avcodec.h HAVE_AVCODEC_H)

file(GLOB SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cxx)

#Here we add our source files

add_executable(avVideo main.cpp avEncoder.cpp avEncoder.h avDecoder.cpp avDecoder.h avConsole.h)
TARGET_LINK_LIBRARIES(avVideo ${FFMPEG_LIBS})





#install(TARGETS carrier EXPORT carrier DESTINATION bin)
