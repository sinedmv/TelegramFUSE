# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/source/build/tdlib-prefix/src/tdlib"
  "/source/build/tdlib-prefix/src/tdlib-build"
  "/source/build/tdlib-prefix"
  "/source/build/tdlib-prefix/tmp"
  "/source/build/tdlib-prefix/src/tdlib-stamp"
  "/source/build/tdlib-prefix/src"
  "/source/build/tdlib-prefix/src/tdlib-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/source/build/tdlib-prefix/src/tdlib-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/source/build/tdlib-prefix/src/tdlib-stamp${cfgdir}") # cfgdir has leading slash
endif()
