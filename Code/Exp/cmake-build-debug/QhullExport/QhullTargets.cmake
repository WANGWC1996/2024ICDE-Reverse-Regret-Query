# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8)
   message(FATAL_ERROR "CMake >= 2.8.0 required")
endif()
if(CMAKE_VERSION VERSION_LESS "2.8.3")
   message(FATAL_ERROR "CMake >= 2.8.3 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.8.3...3.25)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_cmake_targets_defined "")
set(_cmake_targets_not_defined "")
set(_cmake_expected_targets "")
foreach(_cmake_expected_target IN ITEMS Qhull::qhull Qhull::rbox Qhull::qconvex Qhull::qdelaunay Qhull::qvoronoi Qhull::qhalf Qhull::qhull_r Qhull::qhullcpp Qhull::qhullstatic Qhull::qhullstatic_r)
  list(APPEND _cmake_expected_targets "${_cmake_expected_target}")
  if(TARGET "${_cmake_expected_target}")
    list(APPEND _cmake_targets_defined "${_cmake_expected_target}")
  else()
    list(APPEND _cmake_targets_not_defined "${_cmake_expected_target}")
  endif()
endforeach()
unset(_cmake_expected_target)
if(_cmake_targets_defined STREQUAL _cmake_expected_targets)
  unset(_cmake_targets_defined)
  unset(_cmake_targets_not_defined)
  unset(_cmake_expected_targets)
  unset(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT _cmake_targets_defined STREQUAL "")
  string(REPLACE ";" ", " _cmake_targets_defined_text "${_cmake_targets_defined}")
  string(REPLACE ";" ", " _cmake_targets_not_defined_text "${_cmake_targets_not_defined}")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_cmake_targets_defined_text}\nTargets not yet defined: ${_cmake_targets_not_defined_text}\n")
endif()
unset(_cmake_targets_defined)
unset(_cmake_targets_not_defined)
unset(_cmake_expected_targets)


# Create imported target Qhull::qhull
add_executable(Qhull::qhull IMPORTED)

# Create imported target Qhull::rbox
add_executable(Qhull::rbox IMPORTED)

# Create imported target Qhull::qconvex
add_executable(Qhull::qconvex IMPORTED)

# Create imported target Qhull::qdelaunay
add_executable(Qhull::qdelaunay IMPORTED)

# Create imported target Qhull::qvoronoi
add_executable(Qhull::qvoronoi IMPORTED)

# Create imported target Qhull::qhalf
add_executable(Qhull::qhalf IMPORTED)

# Create imported target Qhull::qhull_r
add_library(Qhull::qhull_r SHARED IMPORTED)

set_target_properties(Qhull::qhull_r PROPERTIES
  INTERFACE_LINK_LIBRARIES "m"
)

# Create imported target Qhull::qhullcpp
add_library(Qhull::qhullcpp STATIC IMPORTED)

# Create imported target Qhull::qhullstatic
add_library(Qhull::qhullstatic STATIC IMPORTED)

set_target_properties(Qhull::qhullstatic PROPERTIES
  INTERFACE_LINK_LIBRARIES "m"
)

# Create imported target Qhull::qhullstatic_r
add_library(Qhull::qhullstatic_r STATIC IMPORTED)

set_target_properties(Qhull::qhullstatic_r PROPERTIES
  INTERFACE_LINK_LIBRARIES "m"
)

# Import target "Qhull::qhull" for configuration "Debug"
set_property(TARGET Qhull::qhull APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qhull::qhull PROPERTIES
  IMPORTED_LOCATION_DEBUG "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qhull"
  )

# Import target "Qhull::rbox" for configuration "Debug"
set_property(TARGET Qhull::rbox APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qhull::rbox PROPERTIES
  IMPORTED_LOCATION_DEBUG "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/rbox"
  )

# Import target "Qhull::qconvex" for configuration "Debug"
set_property(TARGET Qhull::qconvex APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qhull::qconvex PROPERTIES
  IMPORTED_LOCATION_DEBUG "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qconvex"
  )

# Import target "Qhull::qdelaunay" for configuration "Debug"
set_property(TARGET Qhull::qdelaunay APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qhull::qdelaunay PROPERTIES
  IMPORTED_LOCATION_DEBUG "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qdelaunay"
  )

# Import target "Qhull::qvoronoi" for configuration "Debug"
set_property(TARGET Qhull::qvoronoi APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qhull::qvoronoi PROPERTIES
  IMPORTED_LOCATION_DEBUG "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qvoronoi"
  )

# Import target "Qhull::qhalf" for configuration "Debug"
set_property(TARGET Qhull::qhalf APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qhull::qhalf PROPERTIES
  IMPORTED_LOCATION_DEBUG "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/qhalf"
  )

# Import target "Qhull::qhull_r" for configuration "Debug"
set_property(TARGET Qhull::qhull_r APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qhull::qhull_r PROPERTIES
  IMPORTED_LOCATION_DEBUG "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/libqhull_rd.8.0.2.dylib"
  IMPORTED_SONAME_DEBUG "@rpath/libqhull_rd.8.0.dylib"
  )

# Import target "Qhull::qhullcpp" for configuration "Debug"
set_property(TARGET Qhull::qhullcpp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qhull::qhullcpp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/libqhullcpp_d.a"
  )

# Import target "Qhull::qhullstatic" for configuration "Debug"
set_property(TARGET Qhull::qhullstatic APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qhull::qhullstatic PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/libqhullstatic_d.a"
  )

# Import target "Qhull::qhullstatic_r" for configuration "Debug"
set_property(TARGET Qhull::qhullstatic_r APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Qhull::qhullstatic_r PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "/Users/wangweicheng/Documents/GitHub/2024ICDE-Reverse-Regret-Query/Code/Exp/cmake-build-debug/libqhullstatic_rd.a"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)