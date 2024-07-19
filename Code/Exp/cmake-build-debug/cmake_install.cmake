# Install script for directory: /Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp

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
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qhull")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qhull" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qhull")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qhull")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/rbox")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rbox" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rbox")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/rbox")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qconvex")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qconvex" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qconvex")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qconvex")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qdelaunay")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qdelaunay" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qdelaunay")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qdelaunay")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qvoronoi")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qvoronoi" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qvoronoi")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qvoronoi")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qhalf")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qhalf" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qhalf")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/qhalf")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/libqhull_rd.8.0.2.dylib"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/libqhull_rd.8.0.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhull_rd.8.0.2.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhull_rd.8.0.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/opt/anaconda3/bin/install_name_tool"
        -id "lib/libqhull_rd.8.0.dylib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/libqhull_rd.dylib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/libqhullcpp_d.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullcpp_d.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullcpp_d.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullcpp_d.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/libqhullstatic_d.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullstatic_d.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullstatic_d.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullstatic_d.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/libqhullstatic_rd.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullstatic_rd.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullstatic_rd.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqhullstatic_rd.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull/QhullTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull/QhullTargets.cmake"
         "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/CMakeFiles/Export/465f793e10159796235ed77137e4ba6d/QhullTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull/QhullTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull/QhullTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull" TYPE FILE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/CMakeFiles/Export/465f793e10159796235ed77137e4ba6d/QhullTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull" TYPE FILE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/CMakeFiles/Export/465f793e10159796235ed77137e4ba6d/QhullTargets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qhull" TYPE FILE FILES
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/QhullExport/QhullConfig.cmake"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/QhullExport/QhullConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qhull_rd.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qhullstatic_d.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qhullstatic_rd.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qhullcpp_d.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libqhull" TYPE FILE FILES
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull/libqhull.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull/geom.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull/io.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull/mem.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull/merge.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull/poly.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull/qhull_a.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull/qset.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull/random.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull/stat.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull/user.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libqhull" TYPE FILE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull/DEPRECATED.txt")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libqhull_r" TYPE FILE FILES
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull_r/libqhull_r.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull_r/geom_r.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull_r/io_r.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull_r/mem_r.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull_r/merge_r.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull_r/poly_r.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull_r/qhull_ra.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull_r/qset_r.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull_r/random_r.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull_r/stat_r.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhull_r/user_r.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libqhullcpp" TYPE FILE FILES
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/Coordinates.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/functionObjects.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/PointCoordinates.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/Qhull.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullError.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullFacet.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullFacetList.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullFacetSet.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullHyperplane.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullIterator.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullLinkedList.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullPoint.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullPoints.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullPointSet.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullQh.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullRidge.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullSet.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullSets.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullStat.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullUser.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullVertex.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/QhullVertexSet.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/RboxPoints.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/RoadError.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/libqhullcpp/RoadLogEvent.h"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/qhulltest/RoadTest.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE RENAME "qhull.1" FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/html/qhull.man")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE RENAME "rbox.1" FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/html/rbox.man")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/qhull" TYPE FILE FILES
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/README.txt"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/REGISTER.txt"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/Announce.txt"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/COPYING.txt"
    "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/index.htm"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/qhull/html" TYPE DIRECTORY FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/html/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/qhull/src" TYPE FILE FILES "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/src/Changes.txt")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
