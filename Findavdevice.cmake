# Locate AVCODEC library
# This module defines
# AVCODEC_LIBRARY, the name of the library to link against
# AVCODEC_FOUND, if false, do not try to link to AVCODEC
# AVCODEC_INCLUDE_DIR, where to find avcodec.h
#

set( AVDEVICE_FOUND "NO" )

find_path( AVDEVICE_INCLUDE_DIR libavdevice/avdevice.h
  HINTS
  $ENV{AVDEVICEDIR}
  PATH_SUFFIXES include 
  PATHS
  /usr/local/include
  /usr/include
  ~/ffmpeg_source
)

#message( "AVCODEC_INCLUDE_DIR is ${AVCODEC_INCLUDE_DIR}" )

find_library( AVDEVICE_LIBRARY
  NAMES avdevice
  HINTS
  $ENV{AVDEVICEDIR}
  PATH_SUFFIXES lib64 lib bin
  PATHS
  /usr/local
  ~/ffmpeg_source
)

#message( "AVCODEC_LIBRARY is ${AVCODEC_LIBRARY}" )

set( AVDEVICE_FOUND "YES" )

#message( "AVCODEC_LIBRARY is ${AVCODEC_LIBRARY}" )
