#pragma once
#include "AccountFwd.h"
#include <algorithm>

extern const size_t MAX_INPUT;
extern const size_t MAX_CHOICE;

namespace validation {
	bool chklogin(const client_number_t&);

	bool isdigit(std::string_view);

	bool isdigit(std::string_view, const char&);

	bool isalpha(std::string_view);

	bool is_currency(const std::string&);

}

class PassException : public std::exception {
	std::vector<const char*> what_args;

public:
	bool empty() {
		return what_args.empty();
	}

	void operator()(const char* err) {
		what_args.emplace_back(err);
	}

	friend std::ostream& operator<<(std::ostream& stream, const PassException& exc) {
		for (auto e : exc.what_args) {
			stream << e;
		}
		return stream;
	}
};

template<typename T>
struct Validation {
	Validation() = delete;
};

template<>
struct Validation<Password> {
	Validation(std::string input) {
		PassException exc;

		if (input.size() < 8)									exc("\nPassword must consist of at least 8 character long\n");
		if (!std::any_of(input.begin(), input.end(), isupper))	exc("\nPassword must consist of at least 1 uppercase letter\n");
		if (!std::any_of(input.begin(), input.end(), islower))	exc("\nPassword must consist of at least 1 lowercase letter\n");
		if (!std::any_of(input.begin(), input.end(), isdigit))	exc("\nPassword must consist of at least 1 digit\n");
		if (std::all_of (input.begin(), input.end(), isalnum))	exc("\nPassword must consist of at least 1 special character\n");

		if (!exc.empty()) throw exc;
	}
};

template<>
struct Validation<Name> {
	Validation(std::string input) {
		if (!validation::isalpha(input))	throw std::runtime_error("\nIncorrect name format!\n");
	}
};

template<>
struct Validation<ClientNumber> {
	Validation(std::string input) {
		if (input.size() > MAX_INPUT)		throw std::runtime_error("\nIncorrect client number format!\n");
		if (!validation::isdigit(input))	throw std::runtime_error("\nClient number Must consist only of digits!\n");
		if (input.size() < 8)				throw std::runtime_error("\nClient number must consist of at least 8 digit long!\n");
	}
};

template<>
struct Validation<currency_t> {
	Validation(std::string input) {
		if (input.size() > MAX_INPUT)			throw std::runtime_error("\nIncorrect currency format!\n");
		if (!validation::is_currency(input))	throw std::runtime_error("\nIncorrect currency format!\n");
	}
};

template<>
struct Validation<size_t> {
	Validation(std::string input) {
		if (input.size() > MAX_INPUT)		throw std::runtime_error("Incorrect format");
		if (!validation::isdigit(input))	throw std::runtime_error("Incorrect format");
	}
};