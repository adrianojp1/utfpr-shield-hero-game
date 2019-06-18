#include "stdafx.h"

sf::Vector2f dot_product(sf::Vector2f v1, sf::Vector2f v2)
{
	return sf::Vector2f(v1.x * v2.x, v1.y * v2.y);
}

sf::Vector2f operator*(sf::Vector2f v1, sf::Vector2f v2)
{
	return dot_product(v1, v2);
}

sf::Vector2f operator/(sf::Vector2f v1, sf::Vector2f v2)
{
	return sf::Vector2f(v1.x / v2.x, v1.y / v2.y);
}

