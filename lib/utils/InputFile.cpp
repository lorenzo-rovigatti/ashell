#include <boost/log/trivial.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <algorithm>
#include "InputFile.h"

using std::string;
using std::map;
using std::set;
using std::vector;

namespace ashell {

InputFile::InputFile() {
	_state = UNPARSED;

	_true_values.insert("true");
	_true_values.insert("1");
	_true_values.insert("yes");
	_true_values.insert("yup");
	_true_values.insert("of course");

	_false_values.insert("false");
	_false_values.insert("0");
	_false_values.insert("no");
	_false_values.insert("nope");
	_false_values.insert("are you crazy?");

	_aggregable_keys = {
		"external_force",
		"observable",
		"column"
	};

	for(auto key : _aggregable_keys) {
		_aggregated_keys[key] = std::vector<InputFile>(0);
	}
}

InputFile::~InputFile() {

}

void InputFile::print_input(char *filename) {
	BOOST_LOG_TRIVIAL(info)<< "Printing the input file as used by ashell in '" << filename << "'";
	FILE *out = fopen(filename, "w");

	for(input_map::iterator it = _keys.begin(); it != _keys.end(); it++) {
		fprintf(out, "%s = %s\n", it->first.c_str(), it->second.value.c_str());
	}

	fclose(out);
}

void InputFile::add_input_from_filename(std::string filename) {
	FILE *inp_file = fopen(filename.c_str(), "r");
	if(inp_file == NULL) {
		_state = ERROR;
		std::string error = boost::str(boost::format("Input file '%s' not found") % filename);
		throw std::runtime_error(error);
	}
	_state = UNPARSED;
	add_input_from_file(inp_file);
	_state = PARSED;
	fclose(inp_file);
}

void InputFile::add_from_command_line_arguments(int argc, char *argv[]) {
	string s_inp("");
	for(int i = 0; i < argc; i++) {
		s_inp += string(argv[i]) + string("\n");
	}
	add_input_from_string(s_inp);
}

int InputFile::_parse_line(std::vector<string>::iterator &it, std::vector<string>::iterator &end, string &key, string &value) {
	string option(*it);
	boost::algorithm::trim(option);

	if(option.size() > 0) {
		std::vector<string> words;
		boost::algorithm::split(words, option, boost::is_any_of("="));

		if(words.size() == 1) {
			BOOST_LOG_TRIVIAL(warning)<< "Malformed line '" << option << "' found. Ignoring it";
			return NOTHING_READ;
		}

		if(words.size() > 2) {
			BOOST_LOG_TRIVIAL(warning)<< "Multiple `=' symbols found in line '" << option << "'. Assuming you know what you are doing.";
			for(auto word : words) {
				words[1] += string("=") + word;
			}
		}

		string my_key = boost::algorithm::trim_copy(words[0]);
		string my_value = boost::algorithm::trim_copy(words[1]);

		if(my_value[0] == '{') {
			// counts the number of open and closed curly brackets 
			size_t open = std::count(my_value.begin(), my_value.end(), '{');
			size_t close = std::count(my_value.begin(), my_value.end(), '}');

			int sum = (int) open - (int) close;

			if(sum < 0) {
				BOOST_LOG_TRIVIAL(warning)<< "Malformed line '" << option << "' found. Extra `}'.";
				return NOTHING_READ;
			}

			if(sum > 0) my_value += string("\n");

			while(sum > 0) {
				it++;

				if(it == end) throw std::runtime_error("Unclosed `{' at the end of file. Aborting");

				string new_line = string(*it);
				boost::algorithm::trim(new_line);

				int n_open = std::count(new_line.begin(), new_line.end(), '{');
				int n_closed = std::count(new_line.begin(), new_line.end(), '}');

				sum += n_open;
				sum -= n_closed;

				if(n_closed > 0) {
					int last_pos = new_line.find_last_of("}");
					string after_end = new_line.substr(last_pos + 1);
					if(after_end.size() > 0) {
						string error = boost::str(boost::format("Found the string '%s' after a closing curly brace. You should either comment it or remove it. Aborting") % after_end);
						throw std::runtime_error(error);
					}
				}

				my_value += new_line;
				if(sum != 0) my_value += string("\n");
			}
		}

		key = my_key;
		value = my_value;
	}
	else return NOTHING_READ;

	return KEY_READ;
}

void InputFile::add_input_from_string(string s_inp) {
	vector<string> tot_lines;
	boost::algorithm::split(tot_lines, s_inp, boost::is_any_of("\n"));
	vector<string> lines;

	for(auto &line : tot_lines) {
		// remove in-line comments
		size_t comment_start = line.find('#');
		if(comment_start != string::npos) line.erase(comment_start, line.size() - comment_start);

		// split the string using ; as a delimiter
		std::vector<string> to_add;
		boost::algorithm::split(to_add, line, boost::is_any_of(";"));

		lines.insert(lines.end(), to_add.begin(), to_add.end());
	}

	std::vector<string>::iterator l_end = lines.end();
	for(std::vector<string>::iterator it = lines.begin(); it != lines.end(); it++) {
		string key, value;
		int res = _parse_line(it, l_end, key, value);

		if(res == KEY_READ) {
			if(std::find(_aggregable_keys.begin(), _aggregable_keys.end(), key) != _aggregable_keys.end()) {
				// if the first element is a '{' then we assume that the whole value is enclosed between braces
				// which therefore have to be removed
				if(value[0] == '{') {
					auto opening_brace = std::find(value.begin(), value.end(), '{');
					value.erase(opening_brace);
					// this is a reverse_iterator
					auto closing_brace_r = std::find(value.rbegin(), value.rend(), '}');
					if(closing_brace_r != value.rend()) {
						// we need the right iterator type... which refers to the element that
						// that is next from the associated reverse_iterator
						auto closing_brace = --(closing_brace_r.base());
						value.erase(closing_brace);
					}
				}

				InputFile new_inp;
				new_inp.add_input_from_string(value);
				_aggregated_keys[key].push_back(new_inp);
			}
			else {
				InputValue new_value(value);

				input_map::iterator old_val = _keys.find(key);
				if(old_val != _keys.end()) {
					string msg = boost::str(boost::format("Overwriting key `%s' (`%s' to `%s')") % key % old_val->second.value % value);
					BOOST_LOG_TRIVIAL(warning)<< msg;
				}
				_keys[key] = value;
			}
		}
	}
}

void InputFile::add_input_from_file(FILE *inp_file) {
	size_t alloc_size;
	char *c_option = NULL;
	string file_contents("");

	int count = 0;
	while(count != -1) {
		count = getline(&c_option, &alloc_size, inp_file);
		if(count != -1) file_contents += string(c_option);
		free(c_option);
		c_option = NULL;
	}

	add_input_from_string(file_contents);
}

input_map::iterator InputFile::_find_value(std::string skey, int mandatory) {
	std::map<string, InputValue>::iterator it = _keys.find(string(skey));
	if(it != _keys.end()) it->second.read++;
	else if(mandatory) {
		string error = boost::str(boost::format("Mandatory key `%s' not found, exiting") % skey);
		throw std::runtime_error(error);
	}

	return it;
}

KeyState InputFile::value_as_string(std::string skey, string &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == _keys.end()) return KeyState::NOT_FOUND;

	dest = it->second.value;

	return KeyState::FOUND;
}

template<typename T>
KeyState InputFile::value_as_integer(std::string skey, T &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == _keys.end()) return KeyState::NOT_FOUND;

	try {
		dest = boost::lexical_cast<T>(it->second.value) + 0.1;
	} catch (boost::bad_lexical_cast &e) {
		string error = boost::str(boost::format("Value '%s' from key '%s' cannot be cast to an integer") % it->second.value % skey);
		throw std::runtime_error(error);
	}

	return KeyState::FOUND;
}

template KeyState InputFile::value_as_integer(std::string skey, int &dest, int mandatory);
template KeyState InputFile::value_as_integer(std::string skey, uint &dest, int mandatory);
template KeyState InputFile::value_as_integer(std::string skey, long long int &dest, int mandatory);
template KeyState InputFile::value_as_integer(std::string skey, ullint &dest, int mandatory);

KeyState InputFile::value_as_bool(std::string skey, bool &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == _keys.end()) return KeyState::NOT_FOUND;

	// make it lower case
	string val = it->second.value;
	std::transform(val.begin(), val.end(), val.begin(), ::tolower);

	set<string>::iterator res = _true_values.find(val);
	if(res != _true_values.end()) dest = true;
	else {
		res = _false_values.find(val);
		if(res != _false_values.end()) dest = false;
		else {
			string error = boost::str(boost::format("boolean key `%s' is invalid (`%s'), aborting.") % skey % val);
			throw std::runtime_error(error);
		}
	}

	return KeyState::FOUND;
}

KeyState InputFile::value_as_char(std::string skey, char &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == _keys.end()) return KeyState::NOT_FOUND;

	dest = it->second.value[0];

	return KeyState::FOUND;
}

KeyState InputFile::value_as_vec3(std::string skey, vec3 &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == _keys.end()) return KeyState::NOT_FOUND;

	std::vector<std::string> spl_line;
	boost::split(spl_line, it->second.value, boost::is_any_of(","), boost::token_compress_on);

	if(spl_line.size() != 3) {
		string error = boost::str(boost::format("Value '%s' from key '%s' should have three fields to be interpreted as a vec3") % it->second.value % skey);
		throw std::runtime_error(error);
	}

	for(auto &token : spl_line) {
		boost::trim(token);
	}

	try {
		dest = vec3(boost::lexical_cast<double>(spl_line[0]), boost::lexical_cast<double>(spl_line[1]), boost::lexical_cast<double>(spl_line[2]));
	} catch (boost::bad_lexical_cast &e) {
		string error = boost::str(boost::format("Value '%s' from key '%s' cannot be interpreted as a vec3") % it->second.value % skey);
		throw std::runtime_error(error);
	}

	return KeyState::FOUND;
}

KeyState InputFile::value_as_int_vector(std::string skey, std::vector<int> &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == _keys.end()) return KeyState::NOT_FOUND;

	std::vector<std::string> spl_line;
	boost::split(spl_line, it->second.value, boost::is_any_of(","), boost::token_compress_on);

	dest.clear();
	for(auto v : spl_line) {
		try {
			boost::trim(v);
			dest.push_back(boost::lexical_cast<int>(v));
		} catch (boost::bad_lexical_cast &e) {
			string error = boost::str(boost::format("The component '%s' of value '%s' from key '%s' cannot be cast to an integer") % v % it->second.value % skey);
			throw std::runtime_error(error);
		}
	}

	return KeyState::FOUND;
}

template<typename number>
KeyState InputFile::value_as_number(std::string skey, number &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == _keys.end()) return KeyState::NOT_FOUND;

	try {
		dest = boost::lexical_cast<number>(it->second.value);
	} catch (boost::bad_lexical_cast &e) {
		string error = boost::str(boost::format("The key '%s' cannot be cast to a floating point") % it->second.value % skey);
		throw std::runtime_error(error);
	}

	return KeyState::FOUND;
}

template KeyState InputFile::value_as_number(std::string skey, float &dest, int mandatory);
template KeyState InputFile::value_as_number(std::string skey, double &dest, int mandatory);

std::vector<InputFile> &InputFile::get_aggregated(std::string key) {
	if(std::find(_aggregable_keys.begin(), _aggregable_keys.end(), key) == _aggregable_keys.end()) {
		std::string error = boost::str(boost::format("The '%s' key is not aggregable") % key);
		throw std::runtime_error(error);
	}

	return _aggregated_keys[key];
}

void InputFile::set_unread_keys() {
	for(input_map::iterator it = _keys.begin(); it != _keys.end(); it++) {
		if(it->second.read == 0) _unread_keys.push_back(it->first);
	}
}
} /* namespace ashell */
