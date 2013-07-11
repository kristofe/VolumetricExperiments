cmake_minimum_required  (VERSION 2.6)
project(VolumetricExperiments)


#set(KDSLIBFILE_PATH "libKDSLib.a" CACHE FILEPATH "Where is KDSLib?")

set(KDSLIB_PATH "/Users/kristofe/Documents/Projects/KDSLib/")
set(KDSLIB_BUILD_PATH ${KDSLIB_PATH}build)
set(KDSLIB_INCLUDE_PATH ${KDSLIB_PATH}include)

#message(${KDSLIBBUILD_PATH})

add_subdirectory(${KDSLIB_PATH} ${KDSLIB_BUILD_PATH})
include_directories(${KDSLIB_INCLUDE_PATH})
link_directories(${KDSLIB_BUILD_PATH})

if(APPLE)
   FIND_LIBRARY(IOKIT_LIBRARY IOKit)
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(OPENGL_LIBRARY OpenGL)

   MARK_AS_ADVANCED(IOKIT_LIBRARY
                     COCOA_LIBRARY
                     OPENGL_LIBRARY)
   SET(EXTRA_LIBS ${IOKIT_LIBRARY} ${COCOA_LIBRARY} ${OPENGL_LIBRARY} libKDSLib.a libglfw3.a )
ENDIF(APPLE)

add_executable(Volumetric main.cpp)
target_link_libraries(Volumetric ${EXTRA_LIBS})
