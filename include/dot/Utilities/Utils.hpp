#pragma once
#include <SFML/Graphics.hpp>

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

	template <typename T>
	static inline bool isIntersecting(const sf::Rect<T>& rect, const sf::Vector2<T>& point)
	{
		return (point.x == rect.left || point.y == rect.top || point.x == (rect.left + rect.width) || point.y == (rect.top + rect.height));
	}
}; // namespace Utils
}; // namespace dot