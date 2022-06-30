#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "TKG2d" for configuration "Debug"
set_property(TARGET TKG2d APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(TKG2d PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/win64/gcc/lib/libTKG2d.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/win64/gcc/bin/libTKG2d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS TKG2d )
list(APPEND _IMPORT_CHECK_FILES_FOR_TKG2d "${_IMPORT_PREFIX}/win64/gcc/lib/libTKG2d.dll.a" "${_IMPORT_PREFIX}/win64/gcc/bin/libTKG2d.dll" )

# Import target "TKG3d" for configuration "Debug"
set_property(TARGET TKG3d APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(TKG3d PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/win64/gcc/lib/libTKG3d.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/win64/gcc/bin/libTKG3d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS TKG3d )
list(APPEND _IMPORT_CHECK_FILES_FOR_TKG3d "${_IMPORT_PREFIX}/win64/gcc/lib/libTKG3d.dll.a" "${_IMPORT_PREFIX}/win64/gcc/bin/libTKG3d.dll" )

# Import target "TKGeomBase" for configuration "Debug"
set_property(TARGET TKGeomBase APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(TKGeomBase PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/win64/gcc/lib/libTKGeomBase.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/win64/gcc/bin/libTKGeomBase.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS TKGeomBase )
list(APPEND _IMPORT_CHECK_FILES_FOR_TKGeomBase "${_IMPORT_PREFIX}/win64/gcc/lib/libTKGeomBase.dll.a" "${_IMPORT_PREFIX}/win64/gcc/bin/libTKGeomBase.dll" )

# Import target "TKBRep" for configuration "Debug"
set_property(TARGET TKBRep APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(TKBRep PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/win64/gcc/lib/libTKBRep.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/win64/gcc/bin/libTKBRep.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS TKBRep )
list(APPEND _IMPORT_CHECK_FILES_FOR_TKBRep "${_IMPORT_PREFIX}/win64/gcc/lib/libTKBRep.dll.a" "${_IMPORT_PREFIX}/win64/gcc/bin/libTKBRep.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
