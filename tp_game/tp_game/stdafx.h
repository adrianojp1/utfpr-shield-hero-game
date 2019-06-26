#pragma once

//======================================================================================================================================//
// === Graphic Libraries === //
#include <SFML/Graphics.hpp>

//======================================================================================================================================//
// === Standart Libraries === //
#include <iostream>
#include <math.h>
#include <time.h>
#include <fstream>

//STL
#include <vector>
#include <list>
#include <set>
#include <deque>

//Codes - Ids

//======================================================================================================================================//
/* === Notification Subtitles === //
	<-ov: int>		If the method is overloaded, shows the definition ordinal.
*/

sf::Vector2f dot_product(sf::Vector2f v1, sf::Vector2f v2); //Or scalar product
sf::Vector2f operator*(sf::Vector2f v1, sf::Vector2f v2);
sf::Vector2f operator/(sf::Vector2f v1, sf::Vector2f v2);

sf::Vector2i operator*(sf::Vector2i vi, sf::Vector2f vf);
sf::Vector2f operator*(sf::Vector2f vf, sf::Vector2i vi);