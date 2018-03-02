#include <boost/log/trivial.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

#include <algorithm>
#include "InputFile.h"

using std::string;
using std::map;
using std::set;
using std::vector;

namespace ashell {

InputFile::InputFile() {
	state = UNPARSED;

	true_values.insert("true");
	true_values.insert("1");
	true_values.insert("yes");
	true_values.insert("yup");
	true_values.insert("of course");

	false_values.insert("false");
	false_values.insert("0");
	false_values.insert("no");
	false_values.insert("nope");
	false_values.insert("are you crazy?");
}

InputFile::~InputFile() {

}

void InputFile::print_input(char *filename) {
	BOOST_LOG_TRIVIAL(info) << "Printing the input file as used by ashell in '" << filename << "'";
	FILE *out = fopen(filename, "w");

	for(input_map::iterator it = keys.begin(); it != keys.end(); it++) {
		fprintf(out, "%s = %s\n", it->first.c_str(), it->second.value.c_str());
	}

	fclose(out);
}

void InputFile::load_from_filename(const char *filename) {
	FILE *inp_file = fopen(filename, "r");
	if(inp_file == NULL) {
		state = ERROR;
		std::string error = boost::str(boost::format("Input file '%s' not found") % filename);
		throw std::runtime_error(error);
	}
	load_from_file(inp_file);
	fclose(inp_file);
	return;
}

void InputFile::add_from_command_line_arguments(int argc, char *argv[]) {
	string s_inp("");
	for(int i = 0; i < argc; i++) s_inp += string(argv[i]) + string("\n");
	add_input_from_string(s_inp);
}

int InputFile::_readLine(std::vector<string>::iterator &it, std::vector<string>::iterator &end, string &key, string &value) {
	string option(*it);
	boost::algorithm::trim(option);

	if (option.size() > 0) {
		std::vector<string> words;
		boost::algorithm::split(words, option, boost::is_any_of("="));
		
		if (words.size() == 1) {
			BOOST_LOG_TRIVIAL(warning) << "Malformed line '" << option << "' found. Ignoring it";
			return NOTHING_READ;
		}

		if (words.size() > 2) {
			BOOST_LOG_TRIVIAL(warning) << "Multiple `=' symbols found in line '" << option << "'. Assuming you know what you are doing.";
			for (unsigned int i = 2; i < words.size(); i ++) words[1] += string("=") + words[i];
		}

		string my_key = boost::algorithm::trim_copy(words[0]);
		string my_value = boost::algorithm::trim_copy(words[1]);

		if(my_value[0] == '{') {
			// counts the number of open and closed curly brackets 
			size_t open = std::count(my_value.begin(), my_value.end(), '{');
			size_t close = std::count(my_value.begin(), my_value.end(), '}');

			int sum = (int)open - (int)close; 

			if (sum < 0) {
				BOOST_LOG_TRIVIAL(warning) << "Malformed line '" << option << "' found. Extra `}'.";
				return NOTHING_READ;
			}

			if (sum > 0) my_value += string("\n");

			while (sum > 0) {
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

void InputFile::load_from_file(FILE *inp_file) {
	state = UNPARSED;
	add_input_from_file(inp_file);
	state = PARSED;
}

void InputFile::add_input_from_string(string s_inp) {
	vector<string> tot_lines;
	boost::algorithm::split(tot_lines, s_inp, boost::is_any_of("\n"));
	vector<string> lines;

	for(vector<string>::iterator it = tot_lines.begin(); it != tot_lines.end(); it++) {
		// remove in-line comments
		size_t comment_start = it->find('#');
		if(comment_start != string::npos) it->erase (comment_start, it->size() - comment_start);

		// split the string using ; as a delimiter
		std::vector<string> to_add;
		boost::algorithm::split(to_add, *it, boost::is_any_of(";"));

		lines.insert(lines.end(), to_add.begin(), to_add.end());
	}

	std::vector<string>::iterator l_end = lines.end();
	for(std::vector<string>::iterator it = lines.begin(); it != lines.end(); it++) {
		string key, value;
		int res = _readLine(it, l_end, key, value);

		if(res == KEY_READ){
			InputValue new_value(value);

			input_map::iterator old_val = keys.find(key);
			if(old_val != keys.end()) {
				string msg = boost::str(boost::format("Overwriting key `%s' (`%s' to `%s')") % key % old_val->second.value % value);
				BOOST_LOG_TRIVIAL(warning) << msg;
			}
			keys[key] = value;
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

input_map::iterator InputFile::_find_value(std::string skey, int mandatory)  {
	std::map<string, InputValue>::iterator it = keys.find(string(skey));
	if(it != keys.end()) it->second.read++;
	else if(mandatory) {
		string error = boost::str(boost::format("Mandatory key `%s' not found, exiting") % skey);
		throw std::runtime_error(error);
	}

	return it;
}

int InputFile::value_as_string(std::string skey, string &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == keys.end()) return KEY_NOT_FOUND;
		
	dest = it->second.value;

	return KEY_FOUND;
}

int InputFile::value_as_int(std::string skey, int &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == keys.end()) return KEY_NOT_FOUND;

	dest = (int) floor(atof(it->second.value.c_str())+0.1);

	return KEY_FOUND;
}

int InputFile::value_as_bool(std::string skey, bool &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == keys.end()) return KEY_NOT_FOUND;

	// make it lower case
	string val = it->second.value;
	std::transform(val.begin(), val.end(), val.begin(), ::tolower);

	set<string>::iterator res = true_values.find(val);
	if(res != true_values.end()) dest = true;
	else {
		res = false_values.find(val);
		if(res != false_values.end()) dest = false;
		else {
			string error = boost::str(boost::format("boolean key `%s' is invalid (`%s'), aborting.") % skey % val);
			throw std::runtime_error(error);
		}
	}

	return KEY_FOUND;
}

int InputFile::value_as_llint(std::string skey, long long int &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == keys.end()) return KEY_NOT_FOUND;

	dest = (long long) floor(atof(it->second.value.c_str())+0.1);

	return KEY_FOUND;
}

int InputFile::value_as_ullint(std::string skey, unsigned long long int &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == keys.end()) return KEY_NOT_FOUND;

	dest = (unsigned long long) floor(atof(it->second.value.c_str())+0.1);

	return KEY_FOUND;
}

int InputFile::value_as_uint(std::string skey, unsigned int &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == keys.end()) return KEY_NOT_FOUND;

	dest = (unsigned int) floor (atof(it->second.value.c_str())+0.1);

	return KEY_FOUND;
}

int InputFile::value_as_char(std::string skey, char &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == keys.end()) return KEY_NOT_FOUND;

	dest = it->second.value[0];

	return KEY_FOUND;
}

template<typename number>
int InputFile::value_as_number(std::string skey, number &dest, int mandatory) {
	input_map::iterator it = _find_value(skey, mandatory);
	if(it == keys.end()) return KEY_NOT_FOUND;

	dest = (number) atof(it->second.value.c_str());

	return KEY_FOUND;
}
template int InputFile::value_as_number(std::string skey, float &dest, int mandatory);
template int InputFile::value_as_number(std::string skey, double &dest, int mandatory);

void InputFile::set_unread_keys() {
	for(input_map::iterator it = keys.begin(); it != keys.end(); it++) {
		if(it->second.read == 0) unread_keys.push_back(it->first);
	}
}
} /* namespace ashell */
