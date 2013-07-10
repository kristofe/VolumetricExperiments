cmake_minimum_required  (VERSION 2.6)
project(VolumetricExperiments)


if(APPLE)
   FIND_LIBRARY(IOKIT_LIBRARY IOKit)
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(OPENGL_LIBRARY OpenGL)

   MARK_AS_ADVANCED(IOKIT_LIBRARY
                     COCOA_LIBRARY
                     OPENGL_LIBRARY)
   SET(EXTRA_LIBS ${IOKIT_LIBRARY} ${COCOA_LIBRARY} ${OPENGL_LIBRARY} libglfw3.a)
ENDIF(APPLE)

add_executable(Volumetric main.cpp)
target_link_libraries(Volumetric ${EXTRA_LIBS})
