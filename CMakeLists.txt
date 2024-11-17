cmake_minimum_required(VERSION 3.14)

project(razer_chroma_sdk VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(_HEADERS
  "src/chroma.hpp"
  "src/RzChromaSDKDefines.h"
  "src/RzChromaSDKTypes.h"
  "src/RzErrors.h"
)

add_library(razer_chroma_sdk INTERFACE)
target_include_directories(razer_chroma_sdk INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

install(TARGETS razer_chroma_sdk ARCHIVE)
install(FILES ${_HEADERS} DESTINATION "include/razer-chroma-sdk")
