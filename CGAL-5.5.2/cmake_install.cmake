# Install script for directory: /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/chengling/.local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xCGAL_Qt5x" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/CGAL/Qt" TYPE DIRECTORY FILES "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/include/CGAL/Qt/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/CGAL" TYPE FILE FILES
    "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/AUTHORS"
    "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/CHANGES.md"
    "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/LICENSE"
    "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/LICENSE.GPL"
    "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/LICENSE.LGPL"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/include/CGAL" REGEX "/\\.svn$" EXCLUDE REGEX "/Qt$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/include/CGAL" REGEX "/\\.svn$" EXCLUDE REGEX "/Qt$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES
    "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/scripts/cgal_create_CMakeLists"
    "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/scripts/cgal_create_cmake_script"
    "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/scripts/cgal_make_macosx_app"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/CGAL" TYPE DIRECTORY FILES "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/cmake/modules/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/CGAL" TYPE FILE FILES "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/cmake/modules/UseCGAL.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/CGAL" TYPE FILE FILES
    "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/lib/cmake/CGAL/CGALConfig.cmake"
    "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/lib/cmake/CGAL/CGALConfigBuildVersion.cmake"
    "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/lib/cmake/CGAL/CGALConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/auxiliary/cgal_create_cmake_script.1")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/CGAL-5.5.2/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
