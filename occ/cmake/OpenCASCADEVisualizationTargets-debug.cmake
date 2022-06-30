#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "TKService" for configuration "Debug"
set_property(TARGET TKService APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(TKService PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/win64/gcc/lib/libTKService.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/win64/gcc/bin/libTKService.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS TKService )
list(APPEND _IMPORT_CHECK_FILES_FOR_TKService "${_IMPORT_PREFIX}/win64/gcc/lib/libTKService.dll.a" "${_IMPORT_PREFIX}/win64/gcc/bin/libTKService.dll" )

# Import target "TKV3d" for configuration "Debug"
set_property(TARGET TKV3d APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(TKV3d PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/win64/gcc/lib/libTKV3d.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/win64/gcc/bin/libTKV3d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS TKV3d )
list(APPEND _IMPORT_CHECK_FILES_FOR_TKV3d "${_IMPORT_PREFIX}/win64/gcc/lib/libTKV3d.dll.a" "${_IMPORT_PREFIX}/win64/gcc/bin/libTKV3d.dll" )

# Import target "TKOpenGl" for configuration "Debug"
set_property(TARGET TKOpenGl APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(TKOpenGl PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/win64/gcc/lib/libTKOpenGl.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/win64/gcc/bin/libTKOpenGl.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS TKOpenGl )
list(APPEND _IMPORT_CHECK_FILES_FOR_TKOpenGl "${_IMPORT_PREFIX}/win64/gcc/lib/libTKOpenGl.dll.a" "${_IMPORT_PREFIX}/win64/gcc/bin/libTKOpenGl.dll" )

# Import target "TKMeshVS" for configuration "Debug"
set_property(TARGET TKMeshVS APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(TKMeshVS PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/win64/gcc/lib/libTKMeshVS.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/win64/gcc/bin/libTKMeshVS.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS TKMeshVS )
list(APPEND _IMPORT_CHECK_FILES_FOR_TKMeshVS "${_IMPORT_PREFIX}/win64/gcc/lib/libTKMeshVS.dll.a" "${_IMPORT_PREFIX}/win64/gcc/bin/libTKMeshVS.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
