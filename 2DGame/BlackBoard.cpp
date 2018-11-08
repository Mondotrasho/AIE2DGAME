#include "BlackBoard.h"



blackboard::blackboard()
= default;


blackboard::~blackboard()
= default;

bool blackboard::set_entry(blackboard_ID, float*)
{
}

bool blackboard::has_entry(blackboard_ID)
{
}

bool blackboard::contains(blackboard_ID)
{
}

bool blackboard::get_type(blackboard_ID)
{
}

bool blackboard::get_entry(blackboard_data_type type, blackboard_data info)
{
	switch(type) { 
		case type_float:
			entries.find(type);
		break;
	case type_int: break;
	case type_char: break;
	case type_bool: break;
	case type_pointer: break;
	default: ;
	}

		
}


bool blackboard::contains(blackboard_data_type info)
{
	//check if entries contains entrys with data type
	switch (info) {
	case type_float:
		//are there any floats
		for (auto e : entries)
		{
			if(e.second.type == type_float)
			{
				return true;
			}
		}
		return false;
	case type_int:
		//are there any ints
		for (auto e : entries)
		{
			if (e.second.type == type_int)
			{
				return true;
			}
		}
		return false;
	case type_char:
		//are there any chars
		for (auto e : entries)
		{
			if (e.second.type == type_char)
			{
				return true;
			}
		}
		return false;
	case type_bool:
		//are there any bools
		for (auto e : entries)
		{
			if (e.second.type == type_bool)
			{
				return true;
			}
		}
		return false;
	case type_pointer:
		//are there any pointers
		for (auto e : entries)
		{
			if (e.second.type == type_pointer)
			{
				return true;
			}
		}
		return false;
	default:
		return false;
	}
}

bool blackboard::get_type(blackboard_data_type)
{

}
