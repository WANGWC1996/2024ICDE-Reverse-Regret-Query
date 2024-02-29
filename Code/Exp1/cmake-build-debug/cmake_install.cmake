# Install script for directory: /Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/qhull")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qhull" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qhull")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qhull")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/rbox")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rbox" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rbox")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rbox")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/qconvex")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qconvex" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qconvex")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qconvex")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/qdelaunay")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qdelaunay" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qdelaunay")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qdelaunay")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/qvoronoi")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qvoronoi" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qvoronoi")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qvoronoi")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/qhalf")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qhalf" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qhalf")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qhalf")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/libqhull_rd.8.0.2.dylib"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/libqhull_rd.8.0.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhull_rd.8.0.2.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhull_rd.8.0.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/usr/bin/install_name_tool"
        -id "lib/libqhull_rd.8.0.dylib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/libqhull_rd.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhull_rd.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhull_rd.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "lib/libqhull_rd.8.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhull_rd.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhull_rd.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/libqhullcpp_d.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullcpp_d.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullcpp_d.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullcpp_d.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/libqhullstatic_d.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullstatic_d.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullstatic_d.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullstatic_d.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/libqhullstatic_rd.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullstatic_rd.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullstatic_rd.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullstatic_rd.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull/QhullTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull/QhullTargets.cmake"
         "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/CMakeFiles/Export/lib/cmake/Qhull/QhullTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull/QhullTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull/QhullTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull" TYPE FILE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/CMakeFiles/Export/lib/cmake/Qhull/QhullTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull" TYPE FILE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/CMakeFiles/Export/lib/cmake/Qhull/QhullTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull" TYPE FILE FILES
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/QhullExport/QhullConfig.cmake"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/QhullExport/QhullConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/qhull_rd.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/qhullstatic_d.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/qhullstatic_rd.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/qhullcpp_d.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libqhull" TYPE FILE FILES
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull/libqhull.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull/geom.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull/io.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull/mem.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull/merge.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull/poly.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull/qhull_a.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull/qset.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull/random.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull/stat.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull/user.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libqhull" TYPE FILE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull/DEPRECATED.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libqhull_r" TYPE FILE FILES
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull_r/libqhull_r.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull_r/geom_r.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull_r/io_r.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull_r/mem_r.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull_r/merge_r.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull_r/poly_r.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull_r/qhull_ra.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull_r/qset_r.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull_r/random_r.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull_r/stat_r.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhull_r/user_r.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libqhullcpp" TYPE FILE FILES
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/Coordinates.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/functionObjects.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/PointCoordinates.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/Qhull.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullError.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullFacet.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullFacetList.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullFacetSet.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullHyperplane.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullIterator.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullLinkedList.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullPoint.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullPoints.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullPointSet.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullQh.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullRidge.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullSet.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullSets.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullStat.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullUser.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullVertex.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/QhullVertexSet.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/RboxPoints.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/RoadError.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/libqhullcpp/RoadLogEvent.h"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/qhulltest/RoadTest.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE RENAME "qhull.1" FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/html/qhull.man")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE RENAME "rbox.1" FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/html/rbox.man")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/qhull" TYPE FILE FILES
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/README.txt"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/REGISTER.txt"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/Announce.txt"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/COPYING.txt"
    "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/index.htm"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/qhull/html" TYPE DIRECTORY FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/html/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/qhull/src" TYPE FILE FILES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/src/Changes.txt")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
