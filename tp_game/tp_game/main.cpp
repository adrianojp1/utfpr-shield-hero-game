//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === Classes Headers === //
#include "Player.h"

//======================================================================================================================================//

const float pixelScale(5.5f); // Window pixel scale

int main()
{
	//Declare window and view
	sf::RenderWindow window(sf::VideoMode(800, 600), "Shield Hero", sf::Style::Close | sf::Style::Titlebar);
	sf::View view(sf::Vector2f{ 0.0f, 0.0f }, (sf::Vector2f)window.getSize());
	view.setSize( (sf::Vector2f) window.getSize()/pixelScale);
	window.setView(view);
	
	//Player sprite
	Player player1(sf::Vector2f{ 0.0f, 0.0f }, 100.0f);

	float deltaTime = 0.0f;
	sf::Clock clock;

	//Main lopp
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		//Window event
		sf::Event evnt;

		//Window poll loop
		while (window.pollEvent(evnt))
		{
			//Close window
			if (evnt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		
		player1.execute(deltaTime);

		window.clear(); //Clear window buffer
		player1.draw(window);
		window.display(); //Show current frame
	}

	return 0;
}