SET(ashell_lib_SOURCES
	ashell.cpp
	boxes/Box.cpp
	boxes/Cuboid.cpp
	Initialiser.cpp
	integrators/Integrator.cpp
	integrators/VelocityVerlet.cpp
	Particles.cpp
	System.cpp
	SystemProperties.cpp
	utils/parse_input.cpp
	utils/Timings.cpp
)

ADD_LIBRARY(_ashell SHARED ${ashell_lib_SOURCES})
TARGET_LINK_LIBRARIES(_ashell ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_ashell PROPERTIES PREFIX "")

# by default, libraries have extension ".dylib" on Mac OS X, but these are
# not recognized by python as modules
IF(APPLE)
    SET_TARGET_PROPERTIES(_ashell PROPERTIES SUFFIX ".so")
ENDIF(APPLE)
