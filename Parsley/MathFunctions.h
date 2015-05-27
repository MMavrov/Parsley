#ifndef __MATH_FUNCTIONS_CLASS_DEFINED__
#define __MATH_FUNCTIONS_CLASS_DEFINED__

#include"Bullet.h"
#include"Ship.h"

class MathFunctions
{
public:
	static sf::Vector2f Normalize(sf::Vector2f);
	static float SignedArea(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);
};

#endif