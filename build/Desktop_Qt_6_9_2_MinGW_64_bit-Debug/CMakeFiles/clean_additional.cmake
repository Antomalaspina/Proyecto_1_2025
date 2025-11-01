# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Space_Invaders_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Space_Invaders_autogen.dir\\ParseCache.txt"
  "Space_Invaders_autogen"
  )
endif()
