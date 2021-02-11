#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "NemaTode::NemaTode" for configuration "Debug"
set_property(TARGET NemaTode::NemaTode APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(NemaTode::NemaTode PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libNemaToded.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS NemaTode::NemaTode )
list(APPEND _IMPORT_CHECK_FILES_FOR_NemaTode::NemaTode "${_IMPORT_PREFIX}/lib/libNemaToded.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
