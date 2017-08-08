#pragma once
#include "stdafx.h"
#include "Person.h"

Name::Name(first_name t_first, last_name t_last)
	: mFirstName(std::move(t_first)), mLastName(std::move(t_last))
{}

Person::Person(first_name t_first, last_name t_last)
	: name(std::move(t_first), std::move(t_last))
{}