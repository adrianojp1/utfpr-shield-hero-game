//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "MyWindow.h"


MyWindow::MyWindow(float viewZoom, sf::Vector2u windowRatio, unsigned int ratioMultiplier)
{
	initializeWindow(windowRatio * ratioMultiplier, "Shield Hero");
	initializeView({ 0.0f, 0.0f }, (sf::Vector2f) pWindow->getSize(), viewZoom);
} // end constr (parameters)

MyWindow::MyWindow()
{
	pWindow = NULL;
	pView = NULL;
} // end constr (no parameters)

MyWindow::~MyWindow()
{
	if(pWindow != NULL)
		delete pWindow;
	if(pView != NULL)
		delete pView;
} // end destr

void MyWindow::initializeWindow(sf::Vector2u size, std::string title)
{
	pWindow = new sf::RenderWindow(sf::VideoMode(size.x, size.y), title, sf::Style::Close | sf::Style::Titlebar);
}

void MyWindow::initializeView(sf::Vector2f center, sf::Vector2f windowSize, float zoom)
{
	pView = new sf::View;
	pView->setCenter(center);
	pView->setSize( windowSize / zoom);
	pWindow->setView(*pView);
}

void MyWindow::execute()
{
	//Window event
	sf::Event evnt;

	//Window event poll loop
	while (this->pollEvent(evnt))
	{
		//Close window
		if (evnt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->close();
	}
}

bool MyWindow::isOpen()
{
	return pWindow->isOpen();
}

bool MyWindow::pollEvent(sf::Event& evnt)
{
	return pWindow->pollEvent(evnt);
}

void MyWindow::close()
{
	pWindow->close();
}

void MyWindow::clear()
{
	pWindow->clear();
}

void MyWindow::display()
{
	pWindow->display();
}

void MyWindow::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
	pWindow->draw(drawable, states);
}

void MyWindow::draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates& states)
{
	pWindow->draw(vertices, vertexCount, type, states);
}

void MyWindow::draw(const sf::VertexBuffer& vertexBuffer, const sf::RenderStates& states)
{
	pWindow->draw(vertexBuffer, states);
}

void MyWindow::draw(const sf::VertexBuffer& vertexBuffer, std::size_t firstVertex, std::size_t vertexCount, const sf::RenderStates& states)
{
	pWindow->draw(vertexBuffer, firstVertex, vertexCount, states);
}
