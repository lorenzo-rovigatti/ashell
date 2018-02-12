/*
 * OutputObservable.h
 *
 *  Created on: 12 feb 2018
 *      Author: lorenzo
 */

#ifndef LIB_OUTPUTOBSERVABLE_H_
#define LIB_OUTPUTOBSERVABLE_H_

#include "consumers/observables/Observable.h"

#include <vector>
#include <fstream>
#include <memory>

namespace ashell {

class OutputObservable {
public:
	OutputObservable(std::string stream_name, ullint print_every);
	virtual ~OutputObservable();

	void add_observable(std::shared_ptr<Observable> obs) {
		_observables.push_back(obs);
	}

	bool is_ready(ullint step);

	void print_output(ullint step);

protected:
	std::vector<std::shared_ptr<Observable> > _observables;
	std::ofstream _output_stream;
	std::ostream *_output;

	ullint _print_every;
	ullint _start_from;
	ullint _stop_at;
};

} /* namespace ashell */

#endif /* LIB_OUTPUTOBSERVABLE_H_ */
