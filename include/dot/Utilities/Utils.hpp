#pragma once

namespace dot
{
namespace Utils
{
	static inline bool isInteger(const std::string& s)
	{
		if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
		
		char * p;
		strtol(s.c_str(), &p, 10);
		return (*p == 0);
	}
};
}; // namespace dot