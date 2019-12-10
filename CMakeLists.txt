cmake_minimum_required(VERSION 2.8.1)
project(face_position)
add_compile_options(-std=c++11)

# set up the libraries dir
set(OpenCV_DIR "/home/rjp/MyOpenCV/opencv-3.4-install/share/OpenCV")
set(dlib_DIR "/home/rjp/MyDilb/install/lib/cmake/dlib")

# set up the variables
set(SRC
  src/detector.cpp
  src/solvePnP.cpp
  src/cfg_handle.cpp
  src/face_pos.cpp
)

# find package
find_package(OpenCV REQUIRED)
find_package(dlib REQUIRED)
find_package(yaml-cpp REQUIRED)

# include dirs
include_directories(
  include/
  ${YAML_CPP_INCLUDE_DIR}
  ${OpenCV_INCLUDE_DIRS}
  dlib::dlib
)

# add executable
add_executable(face_position
  src/main.cpp
  ${SRC}
)

target_link_libraries(face_position
  ${OpenCV_LIBS}
  dlib::dlib
  yaml-cpp
)
