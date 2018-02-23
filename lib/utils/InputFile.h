#ifndef PARSE_INPUT_H_
#define PARSE_INPUT_H_

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <set>

#define UNPARSED 0
#define PARSED 1
#define ERROR 2
#define KEY_NOT_FOUND -1
#define KEY_FOUND 0
#define KEY_INVALID 1

#define INP_EOF -1
#define KEY_READ 0
#define NOTHING_READ 1

namespace ashell {

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
	void load_from_filename(const char *filename);

	/**
	 * @brief Load the keys and values found in the desc file into the given input_file
	 * @param inp
	 * @param desc
	 */
	void load_from_file(FILE *desc);

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

	int value_as_string(const char *skey, std::string &dest, int mandatory);
	int value_as_int(const char *skey, int *dest, int mandatory);
	int value_as_bool(const char *skey, bool *dest, int mandatory);
	int value_as_uint(const char *skey, unsigned int *dest, int mandatory);
	int value_as_llint(const char *skey, long long int *dest, int mandatory);
	int value_as_ullint(const char *skey, unsigned long long int *dest, int mandatory);
	template<typename number> int value_as_number(const char *skey, number *dest, int mandatory);
	int value_as_char(const char *skey, char *dest, int mandatory);

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
	int _readLine(std::vector<std::string>::iterator &it, std::vector<std::string>::iterator &end, std::string &key, std::string &value);

	input_map::iterator _find_value(const char *skey, int mandatory);

	input_map keys;
	std::vector<std::string> unread_keys;
	int state;

	std::set<std::string> true_values;
	std::set<std::string> false_values;
};

}

#endif
