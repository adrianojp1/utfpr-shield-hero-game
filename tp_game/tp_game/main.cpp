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
bool checkCollision(Player* player, Platform* platform, sf::Vector2f* direction, float push);

//======================================================================================================================================//
// === Temporary Pointers === //
Player* player1;
MyWindow* window;

std::vector<Platform*> vPlatforms;

//======================================================================================================================================//
// === Main === //
int main()
{
	//Window: zoom(5x), ratio (4:3), ratio multiplier (250)
	window = new MyWindow(5.0f, { 4, 3 }, 250);

	//Player: initial position (0, 0)
	player1 = new Player(sf::Vector2f{ 0.0f, 0.0f });
	
	//Platforms
	vPlatforms.push_back(new Platform(sf::Color::Magenta, sf::Vector2f(20.0f, 40.0f), sf::Vector2f(60.0f, 30.0f)));
	vPlatforms.push_back(new Platform(sf::Color::Magenta, sf::Vector2f(20.0f, 40.0f), sf::Vector2f(-60.0f, 30.0f)));
	vPlatforms.push_back(new Platform(sf::Color::Green, sf::Vector2f(100.0f, 10.0f), sf::Vector2f(0.0f, 30.0f)));

	//Clocking variables
	float deltaTime = 0.0f; //Time elapsed between loop iterations
	sf::Clock clock; //To get the deltaTime

	//Game loop
	while (window->isOpen())
	{
		deltaTime = clock.restart().asSeconds(); //Iteration clock
		if (deltaTime > 1.0f / 20.f)
			deltaTime = 1.0f / 20.f;

		execute(deltaTime); //Future game executor: execute all objects

		sf::Vector2f collisionDirection;

		for (Platform* platform : vPlatforms) 
		//Check collision between the player and all platforms
		{
			if (checkCollision(player1, platform, &collisionDirection, 0.0f))
				player1->onCollision(collisionDirection);
		}

		window->execute();

		window->clear(); //Clear window buffer

		draw(window); //Future game drawer: draw all objects

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
	
	for (Platform* platform : vPlatforms) //execute all platforms
	{
		platform->execute(deltaTime);
	}
} // end execute

void draw(MyWindow* window)
{
	player1->draw(window);

	for (Platform* platform : vPlatforms) //draw all platforms
	{
		platform->draw(window);
	}
} // end draw

bool checkCollision(Player* player, Platform* platform, sf::Vector2f* collisionDirection, float push)
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

				*collisionDirection = sf::Vector2f(1.0f, 0.0f);
			}
			else
			{
				player->move((-intersectX * (1.0f - push)), 0.0f);
				platform->move((intersectX * push), 0.0f);

				*collisionDirection = sf::Vector2f(-1.0f, 0.0f);
			}
		}
		else
		{ // pushing on the Y axe
			if (deltaY > 0.0f)
			{
				player->move(0.0f, (intersectY * (1.0f - push)));
				platform->move(0.0f, (-intersectY * push));

				*collisionDirection = sf::Vector2f(0.0f, 1.0f);
			}
			else
			{
				player->move(0.0f, (-intersectY * (1.0f - push)));
				platform->move(0.0f, (intersectY * push));

				*collisionDirection = sf::Vector2f(0.0f, -1.0f);
			}
		}
		return true;
	}
	return false;
}

//======================================================================================================================================//
