#pragma once
#include <map>

//123
enum blackboard_data_type {
	type_float,
	type_int,
	type_char,
	type_bool,
	type_pointer
};

//the info
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

//the Bits of the blackboard
enum class blackboard_ID
{
	WantedLevel,
	PlayerLocation,
	Mode
};


class blackboard
{
public:
	blackboard();
	~blackboard();

	bool get_entry(blackboard_ID, float*);
	bool set_entry(blackboard_ID, float*);
	bool has_entry(blackboard_ID);
	bool contains(blackboard_ID);
	bool get_type(blackboard_ID);
	template <class T>
	bool get_entry(blackboard_ID ID, T* value);

	std::map<blackboard_ID, blackboard_data> entries;
};

template<typename T>
bool inline blackboard::get_entry(blackboard_ID ID, T* value)
{
	switch (entries[ID].type) {
	case type_float:
		value = &entries[ID].float_value;
		break;
	case type_int:
		value = &entries[ID].int_value;
		break;
	case type_char:
		value = &entries[ID].char_value;
		break;
	case type_bool:
		value = &entries[ID].bool_value;
		break;
	case type_pointer:
		value = &entries[ID].pointer_value;
		break;
	default:;
	}
}
