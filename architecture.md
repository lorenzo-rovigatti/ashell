# Ashell architecture

## Initialisation

The initialisation order is

* Reading and parsing of the configuration and of the topology
* External forces
* Outputs (and hence observables)
* Potentials

Given this order, external forces, observables and potentials can assume that the configuration and the topology have been already initialised.
