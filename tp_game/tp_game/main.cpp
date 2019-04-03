//=============// Pre-Compiled Header //=============//
#include "stdafx.h"

#include "Animator.h"

const float pixelScale(5.5f); // Window pixel scale

int main()
{
	//Declare window and view
	sf::RenderWindow window(sf::VideoMode(800, 600), "Shield Hero", sf::Style::Close | sf::Style::Titlebar);
	sf::View view(sf::Vector2f{ 0.0f, 0.0f }, (sf::Vector2f)window.getSize());
	view.setSize( (sf::Vector2f) window.getSize()/pixelScale);
	window.setView(view);

	//Load player texture
	sf::Texture texture;
	if (!texture.loadFromFile("shield_hero.png")) 
		{ std::cerr << "Couldn't load player texture! " << std::endl; }
	//Player sprite
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f{ texture.getSize() }/ 2.0f);
	//Set sprite position
	sprite.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	//Main lopp
	while (window.isOpen())
	{
		//Window event
		sf::Event evnt;

		//Window poll loop
		while (window.pollEvent(evnt))
		{
			//Close window
			if (evnt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		//Move the player
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Left
			sprite.move(sf::Vector2f{ -0.05f, 0.0f });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Bottom
			sprite.move(sf::Vector2f{ 0.0f, 0.05f });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Right
			sprite.move(sf::Vector2f{ 0.05f, 0.0f });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) //Up
			sprite.move(sf::Vector2f{ 0.0f, -0.05f });

		window.clear(); //Clear window buffer
		window.draw(sprite);
		window.display(); //Show current frame
	}

	return 0;
}