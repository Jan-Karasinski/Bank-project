#pragma once
#include <string>

typedef std::string first_name;
typedef std::string last_name;

struct Name {
	first_name mFirstName;
	last_name mLastName;

	Name(first_name, last_name);
};

struct Person {
	Name name;

	Person(first_name, last_name);
};