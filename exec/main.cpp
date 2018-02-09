/*
 * main.cpp
 *
 *  Created on: 07 feb 2018
 *      Author: lorenzo
 */

#include "../lib/World.h"

int main(int argc, char *argv[]) {
	auto system = ashell::World::new_system();

	system->run(100);

	return 0;
}
