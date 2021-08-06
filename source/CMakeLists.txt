cmake_minimum_required(VERSION "3.18.0")

project("FvttDbEdit"
  LANGUAGES CXX
  VERSION "1.0.0"
)

#[===[ Global Configuration ]===]

set(THREADS_PREFER_PTHREAD_FLAG YES)
list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

#[===[ Conan Package Dependencies ]===]

include("${PROJECT_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS NO_STD)

#[===[ System Package Dependencies ]===]

find_package("PkgConfig" REQUIRED)
find_package("Threads" REQUIRED)

pkg_check_modules(gtkmm4 REQUIRED IMPORTED_TARGET gtkmm-3.0)

#[===[ CTest Configuration ]===]

include("CTest")
include("Catch")

#[===[ Core Library ]===]

file(GLOB LIBRARY_SOURCES RELATIVE "${PROJECT_SOURCE_DIR}" CONFIGURE_DEPENDS "src/lib/*.cpp")

add_library("fvttdb"
  ${LIBRARY_SOURCES}
)

target_link_libraries("fvttdb" PUBLIC
  "CONAN_PKG::nlohmann_json"
)

target_include_directories("fvttdb" PUBLIC
  "${PROJECT_SOURCE_DIR}/include"
)

target_compile_features("fvttdb" PUBLIC
  "cxx_std_20"
)

target_compile_options("fvttdb" PUBLIC
  $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall>
  $<$<CXX_COMPILER_ID:GNU,Clang>:-Wextra>
  $<$<CXX_COMPILER_ID:GNU,Clang>:-Werror>
  $<$<CXX_COMPILER_ID:GNU,Clang>:-pedantic-errors>
)

target_compile_definitions("fvttdb" PUBLIC
  "JSON_USE_IMPLICIT_CONVERSIONS=0"
)

add_library("FVTT::db" ALIAS "fvttdb")

#[===[ Library Unit Tests ]===]

file(GLOB TEST_SOURCES RELATIVE "${PROJECT_SOURCE_DIR}" CONFIGURE_DEPENDS "src/test/*.cpp")

add_executable("fvtt-tests"
  ${TEST_SOURCES}
)

target_link_libraries("fvtt-tests" PRIVATE
  "FVTT::db"
  "CONAN_PKG::catch2"
)

catch_discover_tests("fvtt-tests")

#[===[ GUI Executable ]===]

file(GLOB GUI_SOURCES RELATIVE "${PROJECT_SOURCE_DIR}" CONFIGURE_DEPENDS "src/app/*.cpp")

add_executable("fvtt-dbedit-gui"
  ${GUI_SOURCES}
)

target_link_libraries("fvtt-dbedit-gui" PUBLIC
  "FVTT::db"
  "PkgConfig::gtkmm4"
  "Threads::Threads"
)

