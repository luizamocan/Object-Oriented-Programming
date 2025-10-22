# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\e_915_luizamocan_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\e_915_luizamocan_autogen.dir\\ParseCache.txt"
  "e_915_luizamocan_autogen"
  )
endif()
