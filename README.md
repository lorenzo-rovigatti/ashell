# ashell

ashell is a proof-of-concept code I am developing to learn modern c++ and to practice object-oriented programming. Its design has been inspired by [HOOMD-blue](http://glotzerlab.engin.umich.edu/hoomd-blue/)'s architecture.

## Building the executable

### Requirements

* CMake >= 2.8
* make
* A c++11-compliant compiler (tested with GCC 5.4)
* A few Boost modules:
    * Boost Python (libboost-python-dev on debian-derived distros)
    * Boost Log (libboost-log-dev) 
    * Boost Signals2 (libboost-signals-dev)

### Compilation

Extract the ashell archive (or download the nightly build via git) and compile it with the following commands:

	cd ashell		# enter the ashell folder
	mkdir build 	# create a new build folder. It is good practice to compile out-of-source
	cd build
	cmake ..		# here you can specify additional options, see next section
	make -j4		# compile ashell. The -jX make option makes it compile the code in parallel by using X threads.

At the end of the compilation the final executable (ashell) will be placed in the build/bin folder.

### cmake options

Here is a list of options that can be passed to cmake during the pre-compilation stage:

* `-DPython=On`			Enables Python bindings
* `-DDebug=ON`				Compiles with debug symbols and without optimisation flags
* `-DG=ON`				Compiles with debug symbols + optimisation flags
* `-DINTEL=ON`				Uses INTEL's compiler suite

## Usage

### Initial configuration

* If the input file contains no `configuration_file` key, `ashell` will attempt to generate a random configuration using the `initial_N` and `initial_box` keys as initial number of particles and box size, respectively.
* Use the `utilities/generate.py` script to set up a configuration of a spherical triangulated mesh. The script, which takes as argument the number of points that will compose the sphere, produces an initial configuration and a topology file.

### Potentials

* `lennard_jones_force`, parameters:
	1. `rc`
	2. `sigma`
* `FENE_force`, parameters:
	1. `k`
	2. `r0`
* `Harmonic force`, parameters:
	1. `k`
	2. `r0`
* `force_triangulated_mesh`, parameters:
	1. `kv` force constant associated to the relative change of the total volume
	2. `ka` force constant associated to the relative change of the total area
	3. `V0_from_conf` boolean, if true `V0` will be initialised by using the volume of the starting configuration
	4. `V0` used only if `V0_from_initial_conf` is absent or set to false
	5. `A0_from_conf` boolean, if true `A0` will be initialised by using the area of the starting configuration
	6. `A0` used only if `A0_from_initial_conf` is absent or set to false
* `force_dihedral`, parameters:
	1. `kb`
	2. `theta0`

## Acknowledgements

* The structure of ashell has been inspired by [HOOMD-blue](http://glotzerlab.engin.umich.edu/hoomd-blue/)
* Eigen 3.3.4 is included in the source tree
* Some utility classes have been taken (and subsequently modified) from [oxDNA](https://sourceforge.net/projects/oxdna/)
