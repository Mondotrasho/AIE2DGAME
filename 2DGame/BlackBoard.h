#pragma once
#include <map>
#include <vector>

enum blackboard_data_type {
	type_float,
	type_int,
	type_char,
	type_bool,
	type_pointer
};


struct blackboard_data {

	blackboard_data_type type;

	union {
		float float_value;
		int int_value;
		char char_value;
		bool bool_value;
		void* pointer_value;
	};
};


class blackboard
{
public:
	blackboard();
	~blackboard();

	bool get_entry(blackboard_data_type, blackboard_data);
	bool set_entry(blackboard_data_type, blackboard_data);
	bool has_entry(blackboard_data_type);
	bool contains(blackboard_data_type);
	bool get_type(blackboard_data_type);

	std::map<int, blackboard_data> entries;
};

class alt_blackboard
{
	

	std::vector<> scribblings;
};

