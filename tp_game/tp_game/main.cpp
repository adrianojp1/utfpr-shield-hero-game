#include <SFML/Graphics.hpp>
#include <iostream>

const float pixelScale(5.5f);

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

	//Loop principal
	while (window.isOpen())
	{
		//Objeto evento
		sf::Event event;

		//Verificação de eventos da janela
		while (window.pollEvent(event))
		{
			//Verifica se janela foi fechada
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(); //Limpa frame anterior
		window.draw(sprite);
		window.display(); //Mostra frame atual
	}

	return 0;
}