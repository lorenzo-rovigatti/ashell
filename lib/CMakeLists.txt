SET(ashell_lib_SOURCES
	utils/parse_input.cpp
	utils/Timings.cpp
	System.cpp
)

ADD_LIBRARY(_ashell SHARED ${ashell_lib_SOURCES})
TARGET_LINK_LIBRARIES(_ashell ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_ashell PROPERTIES PREFIX "")

# by default, libraries have extension ".dylib" on Mac OS X, but these are
# not recognized by python as modules
if(APPLE)
    SET_TARGET_PROPERTIES(_ashell PROPERTIES SUFFIX ".so")
endif(APPLE)
