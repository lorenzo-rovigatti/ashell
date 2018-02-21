SET(ashell_lib_SOURCES
	ashell.cpp
	boxes/Box.cpp
	boxes/Cuboid.cpp
	computers/Computer.cpp
	computers/ForceComputer.cpp
	computers/ForceLink.cpp
	computers/ForceTwoBodyIsotropic.cpp
	computers/observables/Configuration.cpp
	computers/observables/Observable.cpp
	computers/observables/KineticEnergy.cpp
	computers/observables/PotentialEnergy.cpp
	computers/observables/TotalEnergy.cpp
	computers/observables/Step.cpp
	Initialiser.cpp
	integrators/Integrator.cpp
	integrators/VelocityVerlet.cpp
	OutputObservable.cpp
	Particles.cpp
	System.cpp
	SystemProperties.cpp
	utils/parse_input.cpp
	utils/Timings.cpp
	World.cpp
)

ADD_LIBRARY(_ashell SHARED ${ashell_lib_SOURCES})
TARGET_LINK_LIBRARIES(_ashell ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_ashell PROPERTIES PREFIX "")

# by default, libraries have extension ".dylib" on Mac OS X, but these are
# not recognized by python as modules
IF(APPLE)
    SET_TARGET_PROPERTIES(_ashell PROPERTIES SUFFIX ".so")
ENDIF(APPLE)

ADD_CUSTOM_COMMAND(
        TARGET _ashell POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/test.py
                ${CMAKE_CURRENT_BINARY_DIR})
                