# This project is designed
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT( OpenCVHero )
# based on http://www.cmake.org/cmake/help/examples.html

#-----------------------------------------------------------------------------
# Find modules
FIND_PACKAGE( OpenCV )
FIND_PACKAGE( FMOD )
#-----------------------------------------------------------------------------

include_directories("${PROJECT_BINARY_DIR}")

add_executable( DisplayOpenCVHero
  main.cpp
  core/FrameManager.h
  core/FrameManager.cpp
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
