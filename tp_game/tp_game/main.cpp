#include <SFML/Graphics.hpp>

int main()
{
	//Declara objeto janela
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML");

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
		window.display(); //Mostra frame atual
	}

	return 0;
}