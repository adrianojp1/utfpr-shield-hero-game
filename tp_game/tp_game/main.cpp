//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === Classes Headers === //
#include "Player.h"
#include "MyWindow.h"
#include "Block.h"

//======================================================================================================================================//
// === Temporary Functions Declaration === //
void execute(float deltaTime);
void draw(MyWindow* window);

//Collision
bool checkCollision(Entity* player, Entity* block, sf::Vector2f* collisionDirection, float push);

//======================================================================================================================================//
// === Temporary Pointers === //
Player* player1;
MyWindow* window;

std::vector<Block*> vBlocks;

//======================================================================================================================================//
// === Main === //
int main()
{
	//Window: zoom(5x), ratio (4:3), ratio multiplier (250)
	window = new MyWindow;

	//Player: initial position (0, 0)
	player1 = new Player(sf::Vector2f{ -32.0f, 0.0f });
	
	//Blocks
	for (int i = -4; i < 0; i++) {
		vBlocks.push_back(new Block(sf::Vector2f(float(blockNS::blockSize.x * i), 20.0f)));
		vBlocks.push_back(new Block(sf::Vector2f(float(blockNS::blockSize.x * i + blockNS::blockSize.x*6), 20.0f)));
	}

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

		for (Block* block : vBlocks) 
		//Check collision between the player and all platforms
		{
			if (checkCollision(static_cast<Entity*>(player1), static_cast<Entity*>(block), &collisionDirection, 0.0f))
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
	
	for (Block* block : vBlocks) //execute all platforms
	{
		block->execute(deltaTime);
	}
} // end execute

void draw(MyWindow* window)
{
	player1->draw(window);

	for (Block* block : vBlocks) //draw all platforms
	{
		block->draw(window);
	}
} // end draw

bool checkCollision(Entity* player, Entity* block, sf::Vector2f* collisionDirection, float push)
{
	sf::Vector2f otherPosition = block->getPosition();
	sf::Vector2f otherHalfSize = block->getCollider()->getSize() / 2.0f;
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
				block->move((-intersectX * push), 0.0f);

				*collisionDirection = sf::Vector2f(1.0f, 0.0f);
			}
			else
			{
				player->move((-intersectX * (1.0f - push)), 0.0f);
				block->move((intersectX * push), 0.0f);

				*collisionDirection = sf::Vector2f(-1.0f, 0.0f);
			}
		}
		else
		{ // pushing on the Y axe
			if (deltaY > 0.0f)
			{
				player->move(0.0f, (intersectY * (1.0f - push)));
				block->move(0.0f, (-intersectY * push));

				*collisionDirection = sf::Vector2f(0.0f, 1.0f);
			}
			else
			{
				player->move(0.0f, (-intersectY * (1.0f - push)));
				block->move(0.0f, (intersectY * push));

				*collisionDirection = sf::Vector2f(0.0f, -1.0f);
			}
		}
		return true;
	}
	return false;
}

//======================================================================================================================================//
