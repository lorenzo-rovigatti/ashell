# BEGIN TO COMPILE STUFF
IF(CMAKE_BUILD_TYPE MATCHES Debug)
	SET(exe_name ashell_debug)
ELSE()
	SET(exe_name ashell)
ENDIF()

SET(ashell_SOURCES
	main.cpp
)

ADD_EXECUTABLE(${exe_name} ${ashell_SOURCES})
TARGET_LINK_LIBRARIES(${exe_name} _ashell)
