#pragma once
#include "stdafx.h"
#include <regex>
#include "Validation.h"
#include "Storage.h"

extern const size_t MAX_INPUT  = 19;
extern const size_t MAX_CHOICE = 10;

namespace validation {

	bool chklogin(const client_number_t& cn) {
		if (Storage::FindAccount(cn) == nullptr)
			return true;
		return false;
	}

	bool isdigit(std::string_view s) {
		for (char c : s) {
			if (c < -1) return false; // for diacritic marks
			if (!::isdigit(c)) return false;
		}
		return true;
	}

	bool isdigit(std::string_view s, const char& x) {
		for (char c : s) {
			if (c < -1) return false; // for diacritic marks
			if (!::isdigit(c) && c != x) return false;
		}
		return true;
	}

	bool isalpha(std::string_view s) {
		for (char c : s) {
			if (c < -1) return false; // for diacritic marks
			if (!::isalpha(c))
				return false;
		}
		return true;
	}

	bool is_currency(const std::string& s) {
		static const std::regex pat("([0-9]*[.][0-9]{1,2})|([0-9]*[1-9])");
		return std::regex_match(s, pat);
	}

}