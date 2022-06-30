#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "TKernel" for configuration "Debug"
set_property(TARGET TKernel APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(TKernel PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/win64/gcc/lib/libTKernel.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/win64/gcc/bin/libTKernel.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS TKernel )
list(APPEND _IMPORT_CHECK_FILES_FOR_TKernel "${_IMPORT_PREFIX}/win64/gcc/lib/libTKernel.dll.a" "${_IMPORT_PREFIX}/win64/gcc/bin/libTKernel.dll" )

# Import target "TKMath" for configuration "Debug"
set_property(TARGET TKMath APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(TKMath PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/win64/gcc/lib/libTKMath.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/win64/gcc/bin/libTKMath.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS TKMath )
list(APPEND _IMPORT_CHECK_FILES_FOR_TKMath "${_IMPORT_PREFIX}/win64/gcc/lib/libTKMath.dll.a" "${_IMPORT_PREFIX}/win64/gcc/bin/libTKMath.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
