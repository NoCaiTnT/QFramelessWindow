#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "QWindowKit::Core" for configuration "Debug"
set_property(TARGET QWindowKit::Core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(QWindowKit::Core PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libQWKCore.so"
  IMPORTED_SONAME_DEBUG "libQWKCore.so"
  )

list(APPEND _cmake_import_check_targets QWindowKit::Core )
list(APPEND _cmake_import_check_files_for_QWindowKit::Core "${_IMPORT_PREFIX}/lib/libQWKCore.so" )

# Import target "QWindowKit::Widgets" for configuration "Debug"
set_property(TARGET QWindowKit::Widgets APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(QWindowKit::Widgets PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libQWKWidgets.so"
  IMPORTED_SONAME_DEBUG "libQWKWidgets.so"
  )

list(APPEND _cmake_import_check_targets QWindowKit::Widgets )
list(APPEND _cmake_import_check_files_for_QWindowKit::Widgets "${_IMPORT_PREFIX}/lib/libQWKWidgets.so" )

# Import target "QWindowKit::Quick" for configuration "Debug"
set_property(TARGET QWindowKit::Quick APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(QWindowKit::Quick PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libQWKQuick.so"
  IMPORTED_SONAME_DEBUG "libQWKQuick.so"
  )

list(APPEND _cmake_import_check_targets QWindowKit::Quick )
list(APPEND _cmake_import_check_files_for_QWindowKit::Quick "${_IMPORT_PREFIX}/lib/libQWKQuick.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
