## Design issues

* Add support for multiple types of topological links (i.e. link or angles or dihedrals with different types that may be handled by different potentials)
* Many classes initialise their internal references to SystemDefinitions by using World::current_system. This might generate problems down the road
