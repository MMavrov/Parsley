#include"MathFunctions.h"

sf::Vector2f MathFunctions::Normalize(sf::Vector2f vector)
{
	float length = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	return sf::Vector2f(vector.x / length, vector.y / length);
}

float MathFunctions::SignedArea(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}