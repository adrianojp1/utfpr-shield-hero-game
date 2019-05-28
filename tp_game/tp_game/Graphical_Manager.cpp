//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Graphical_Manager.h"


Graphical_Manager::Graphical_Manager() :
	sf::RenderWindow(sf::VideoMode(windowNS::windowRatio.x * windowNS::ratioMultiplier, windowNS::windowRatio.y * windowNS::ratioMultiplier),
					 windowNS::windowName,
					 sf::Style::Close | sf::Style::Titlebar)
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initializeView({ 0.0f, 0.0f }, (sf::Vector2f) this->getSize(), windowNS::viewZoom);
} // end constr

Graphical_Manager::~Graphical_Manager()
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if(pView != NULL)
		delete pView;
} // end destr

void Graphical_Manager::initializeView(sf::Vector2f center, sf::Vector2f windowSize, float zoom)
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	pView = new sf::View;
	pView->setCenter(center);
	pView->setSize( windowSize / zoom);
	this->setView(*pView);
} // end initializeView

void Graphical_Manager::execute()
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//Window event
	sf::Event evnt;

	//Window event poll loop
	while (this->pollEvent(evnt))
	{
		//Close window
		if (evnt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->close();
	}
} // end execute

void Graphical_Manager::setViewCenter(sf::Vector2f center)
{
	pView->setCenter(center);
}

void Graphical_Manager::moveView(sf::Vector2f offset)
{
	pView->move(offset);
}

void Graphical_Manager::console_log(std::string log)
{
	if(consoleNS::CONSOLE_LOG)
		std::cerr << log << std::endl;
}