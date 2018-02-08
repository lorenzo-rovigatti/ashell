# ashell

## Building the executable

### Requirements

* CMake >= 2.8
* make
* c++11-compliant compiler (tested with GCC 5.4)
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

* `-DDebug=ON`				Compiles with debug symbols and without optimisation flags
* `-DG=ON`					Compiles with debug symbols + optimisation flags
* `-DINTEL=ON`				Uses INTEL's compiler suite

## Acknowledgements

* The structure of ashell has been inspired by [HOOMD-blue](http://glotzerlab.engin.umich.edu/hoomd-blue/)
* Eigen 3.3.4 is included in the source 
