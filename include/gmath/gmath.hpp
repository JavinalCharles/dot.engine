#include <cstdlib>
#include <cmath>
#include <SFML/System/Vector2.hpp>

namespace gmath
{
	float hypot(sf::Vector2f p1, sf::Vector2f p2);

};

using std::sqrt;
using std::pow;

float gmath::hypot(sf::Vector2f p1, sf::Vector2f p2)
{
	return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

