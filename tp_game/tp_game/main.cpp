//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === Classes Headers === //
#include "Player.h"
#include "MyWindow.h"
#include "Platform.h"

//======================================================================================================================================//
// === Temporary Functions Declaration === //
void execute(float deltaTime);
void draw(MyWindow* window);

//Collision
bool checkCollision(Player* player, Platform* platform, float push);

//======================================================================================================================================//
// === Temporary Pointers === //
Player* player1;
MyWindow* window;
Platform* platform1;

//======================================================================================================================================//
// === Main === //
int main()
{
	//Window: zoom(5x), ratio (4:3), ratio multiplier (250)
	window = new MyWindow(5.0f, { 4, 3 }, 250);

	//Player: initial position (0, 0), speed (50), jump height (100)
	player1 = new Player(sf::Vector2f{ 0.0f, 0.0f }, 50.0f, 100.0f);
	
	//Platform: 
	platform1 = new Platform(sf::Color::Magenta, sf::Vector2f(20.0f, 20.0f), sf::Vector2f(40.0f, 0.0f));

	//Clocking variables
	float deltaTime = 0.0f; //Time elapsed between loop iterations
	sf::Clock clock; //To get the deltaTime

	//Game loop
	while (window->isOpen())
	{
		deltaTime = clock.restart().asSeconds(); //Iteration clock

		execute(deltaTime); //Future game executor

		checkCollision(player1, platform1, 0.5f);

		window->execute();
		window->clear(); //Clear window buffer

		draw(window); //Future game drawer

		window->display(); //Show current frame
	} // end game loop

	return 0;
} // end main

//======================================================================================================================================//
// === Temporary Functions Definitions === //
void execute(float deltaTime)
{
	// ========== Window ========== //
	//window->execute();

	// ========== Objects ========== //
	player1->execute(deltaTime);
	platform1->execute(deltaTime);

} // end execute

void draw(MyWindow* window)
{
	player1->draw(window);
	platform1->draw(window);
} // end draw

bool checkCollision(Player* player, Platform* platform, float push)
{
	sf::Vector2f otherPosition = platform->getPosition();
	sf::Vector2f otherHalfSize = platform->getCollider()->getSize() / 2.0f;
	sf::Vector2f thisPosition = player->getPosition();
	sf::Vector2f thisHalfSize = player->getCollider()->getSize() / 2.0f;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f); // clumping push between 0.0f and 1.0f

		if (intersectX > intersectY)// = (abs(intersectX) < abs(intersectY))
		{ // pushing on the X axe
			if (deltaX > 0.0f)
			{
				
				player->move((intersectX * (1.0f - push)), 0.0f);
				platform->move((-intersectX * push), 0.0f);
			}
			else
			{
				player->move((-intersectX * (1.0f - push)), 0.0f);
				platform->move((intersectX * push), 0.0f);
			}
		}
		else
		{ // pushing on the Y axe
			if (deltaY > 0.0f)
			{
				player->move(0.0f, (intersectY * (1.0f - push)));
				platform->move(0.0f, (-intersectY * push));
			}
			else
			{
				player->move(0.0f, (-intersectY * (1.0f - push)));
				platform->move(0.0f, (intersectY * push));
			}
		}
		return true;
	}
	return false;
}

//======================================================================================================================================//
