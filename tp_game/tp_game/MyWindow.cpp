//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "MyWindow.h"


MyWindow::MyWindow(float viewZoom, sf::Vector2u windowRatio, unsigned int ratioMultiplier) :
	sf::RenderWindow(sf::VideoMode(windowRatio.x * ratioMultiplier, windowRatio.y * ratioMultiplier),
					 "Shield Hero",
					 sf::Style::Close | sf::Style::Titlebar)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initializeView({ 0.0f, 0.0f }, (sf::Vector2f) this->getSize(), viewZoom);
} // end constr (parameters)

MyWindow::MyWindow()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	pView = NULL;
} // end constr (no parameters)

MyWindow::~MyWindow()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if(pView != NULL)
		delete pView;
} // end destr

void MyWindow::initializeView(sf::Vector2f center, sf::Vector2f windowSize, float zoom)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	pView = new sf::View;
	pView->setCenter(center);
	pView->setSize( windowSize / zoom);
	this->setView(*pView);
} // end initializeView

void MyWindow::execute()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

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

void MyWindow::setViewCenter(sf::Vector2f center)
{
	pView->setCenter(center);
}

void MyWindow::moveView(sf::Vector2f offset)
{
	pView->move(offset);
}

void MyWindow::console_log(std::string log)
{
	if(console::CONSOLE_LOG)
		std::cerr << log << std::endl;
}