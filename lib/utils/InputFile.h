#ifndef PARSE_INPUT_H_
#define PARSE_INPUT_H_

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "../defs.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <cmath>
#include <string>
#include <map>
#include <set>

#define UNPARSED 0
#define PARSED 1
#define ERROR 2

#define INP_EOF -1
#define KEY_READ 0
#define NOTHING_READ 1

namespace ashell {

enum class KeyState {
	NOT_FOUND = -1,
	FOUND = 0,
};

struct InputValue {
	std::string value;
	int read;

	InputValue() : value(""), read(0) {}
	InputValue(std::string v) : value(v), read(0) {}
};

typedef std::map<std::string, InputValue> input_map;
class InputFile {
public:
	InputFile();
	virtual ~InputFile();

	/**
	 * @brief Load the keys and values found in the filename into the given input_file
	 * This function is a simple wrapper around loadInput so that it is possible to accept a
	 * filename instead of a file descriptor as input.
	 * @param inp
	 * @param filename
	 */
	void add_input_from_filename(std::string filename);

	/**
	 * @brief Add the keys and values found in the desc file to the given input_file.
	 * @param inp target input_file structure
	 * @param desc input file to be parsed
	 */
	void add_input_from_file(FILE *desc);

	/**
	 * @brief Add the keys and values found in the string to the given input_file.
	 * @param inp target input_file structure
	 * @param s_inp string to be parsed
	 */
	void add_input_from_string(std::string s_inp);

	/**
	 * @brief Add the keys and values stored in argv to the given input_file
	 * @param inp target input_file structure
	 * @param argc number of options
	 * @param argv array of options
	 */
	void add_from_command_line_arguments(int argc, char *argv[]);

	/**
	 * @brief Print out all the keys and values stored in the given input_file structure.
	 * @param inp
	 * @param filename
	 */
	void print_input(char *filename);

	KeyState value_as_string(std::string skey, std::string &dest, int mandatory);
	template<typename T> KeyState value_as_integer(std::string skey, T &dest, int mandatory);
	KeyState value_as_bool(std::string skey, bool &dest, int mandatory);
	KeyState value_as_char(std::string skey, char &dest, int mandatory);
	KeyState value_as_vec3(std::string skey, vec3 &dest, int mandatory);
	KeyState value_as_int_vector(std::string skey, std::vector<int> &dest, int mandatory);
	template<typename number> KeyState value_as_number(std::string skey, number &dest, int mandatory);

	std::vector<InputFile> &get_aggregated(std::string key);

	void set_unread_keys();

private:
	/**
	 * @brief Parse a line of the input file
	 * This function allocates memory for the key and the value.
	 * @param it iterator begin position
	 * @param end iterator end position
	 * @param key
	 * @param value
	 * @return INP_EOF if EOF, NOTHING_READ if the line is malformed, empty or commented and KEY_READ otherwise.
	 */
	int _parse_line(std::vector<std::string>::iterator &it, std::vector<std::string>::iterator &end, std::string &key, std::string &value);

	input_map::iterator _find_value(std::string skey, int mandatory);

	input_map _keys;
	std::vector<std::string> _aggregable_keys;
	std::map<std::string, std::vector<InputFile>> _aggregated_keys;
	std::vector<std::string> _unread_keys;
	int _state;

	std::set<std::string> _true_values;
	std::set<std::string> _false_values;
};

}

#endif
