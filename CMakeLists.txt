CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT( OpenCVHero )
# based on http://www.cmake.org/cmake/help/examples.html

#-----------------------------------------------------------------------------
# Find modules
#FIND_PACKAGE( OpenCV 3 REQUIRED )
FIND_PACKAGE( OpenCV 3 HINTS /usr/local/opt/opencv3 )
#-----------------------------------------------------------------------------

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Add OpenCV headers location to your include paths
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( DisplayOpenCVHero
  main.cpp
  model/Symbol.h
  model/Symbol.cpp
  music/MusicManager.h
  music/MusicManager.cpp
  util/cStream.h
  util/cStream.cpp
  util/ImgUtil.h
  util/ImgUtil.cpp
  util/videoWriter.h
  util/videoWriter.cpp
)
target_link_libraries( DisplayOpenCVHero ${OpenCV_LIBS} )
