SET(ashell_lib_SOURCES
	ashell.cpp
	boxes/Box.cpp
	boxes/BoxFactory.cpp
	boxes/Cuboid.cpp
	computers/Computer.cpp
	computers/external_forces/ConstantForce.cpp
	computers/external_forces/ExternalForce.cpp
	computers/external_forces/ForceFactory.cpp
	computers/ForceComputer.cpp
	computers/ForceDihedral.cpp
	computers/ForceLink.cpp
	computers/ForceTwoBodyIsotropic.cpp
	computers/ForceComputerFactory.cpp
	computers/observables/Cogli1Configuration.cpp
	computers/observables/Configuration.cpp
	computers/observables/ObservableFactory.cpp
	computers/observables/Observable.cpp
	computers/observables/KineticEnergy.cpp
	computers/observables/PotentialEnergy.cpp
	computers/observables/TotalEnergy.cpp
	computers/observables/Step.cpp
	computers/observables/StrainInvariants.cpp
	Initialiser.cpp
	updaters/integrators/Integrator.cpp
	updaters/integrators/VelocityVerlet.cpp
	updaters/thermostats/Andersen.cpp
	updaters/thermostats/ThermostatFactory.cpp
	updaters/Updater.cpp
	OutputObservable.cpp
	Particles.cpp
	System.cpp
	SystemProperties.cpp
	utils/InputFile.cpp
	utils/MathUtils.cpp
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
                