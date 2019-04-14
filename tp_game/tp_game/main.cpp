//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === Classes Headers === //
#include "Player.h"
#include "MyWindow.h"

//======================================================================================================================================//
// === Temporary Functions Declaration === //
void execute(float deltaTime);
void draw(MyWindow* window);

//======================================================================================================================================//
// === Temporary Pointers === //
Player* player1;
MyWindow* window;

//======================================================================================================================================//
// === Main === //
int main()
{

	//Player: initial position (0, 0), speed (50), jump height (100)
	player1 = new Player(sf::Vector2f{ 0.0f, 0.0f }, 50.0f, 100.0f);
	//Window: zoom(5x), ratio (4:3), ratio multiplier (250)
	window = new MyWindow(5.0f, { 4, 3 }, 250);

	//Clocking variables
	float deltaTime = 0.0f; //Time elapsed between loop iterations
	sf::Clock clock; //To get the deltaTime

	//Game loop
	while (window->isOpen())
	{
		deltaTime = clock.restart().asSeconds(); //Iteration clock

		execute(deltaTime); //Future game executor
		//window.execute();
		//player1.execute(deltaTime);

		window->clear(); //Clear window buffer

		//player1.draw(&window);
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
	window->execute();

	// ========== Objects ========== //
	player1->execute(deltaTime);

} // end execute

void draw(MyWindow* window)
{
	player1->draw(window);
} // end draw

//======================================================================================================================================//
