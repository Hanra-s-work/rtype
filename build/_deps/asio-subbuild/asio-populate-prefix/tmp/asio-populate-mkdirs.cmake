# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/floks/refactored/rtype/build/_deps/asio-src"
  "/home/floks/refactored/rtype/build/_deps/asio-build"
  "/home/floks/refactored/rtype/build/_deps/asio-subbuild/asio-populate-prefix"
  "/home/floks/refactored/rtype/build/_deps/asio-subbuild/asio-populate-prefix/tmp"
  "/home/floks/refactored/rtype/build/_deps/asio-subbuild/asio-populate-prefix/src/asio-populate-stamp"
  "/home/floks/refactored/rtype/build/_deps/asio-subbuild/asio-populate-prefix/src"
  "/home/floks/refactored/rtype/build/_deps/asio-subbuild/asio-populate-prefix/src/asio-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/floks/refactored/rtype/build/_deps/asio-subbuild/asio-populate-prefix/src/asio-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/floks/refactored/rtype/build/_deps/asio-subbuild/asio-populate-prefix/src/asio-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
