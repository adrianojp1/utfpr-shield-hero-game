//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Graphical_Manager.h"

//======================================================================================================================================//
// === Static initializations === //
const sf::Vector2u Graphical_Manager::windowRatio = { 4, 3 };
const unsigned int Graphical_Manager::ratioMultiplier = 250;
const std::string Graphical_Manager::windowName = "Shield Hero";
const sf::Vector2u Graphical_Manager::windowSize = { windowRatio.x * ratioMultiplier, windowRatio.y * ratioMultiplier };

const float Graphical_Manager::viewZoom = 4.0f;

const bool Graphical_Manager::CONSOLE_LOG = false;
const bool Graphical_Manager::COLLISION_DBG = false;

const std::string Graphical_Manager::menu_Ft_Fp = "Fonts/romulus.ttf";

const std::string Graphical_Manager::player_idle_Sp_Fp = "Media/shield-hero/shield_hero-idle.png";
const std::string Graphical_Manager::player_walk_Sp_Fp = "Media/shield-hero/shield_hero-walk.png";
const std::string Graphical_Manager::player_def1_Sp_Fp = "Media/shield-hero/shield_hero-def1.png";
const std::string Graphical_Manager::player_def2_Sp_Fp = "Media/shield-hero/shield_hero-def2.png";
const std::string Graphical_Manager::player_die_Sp_Fp  = "Media/shield-hero/shield_hero-die.png";

const std::string Graphical_Manager::orc_idle_Sp_Fp = "Media/orc/orc-idle.png";
const std::string Graphical_Manager::orc_walk_Sp_Fp = "Media/orc/orc-walk.png";
const std::string Graphical_Manager::orc_atk_Sp_Fp  = "Media/orc/orc-atk.png";
const std::string Graphical_Manager::orc_die_Sp_Fp  = "Media/orc/orc-die.png";

//======================================================================================================================================//
// === Graphical_Manager methods === //
Graphical_Manager::Graphical_Manager() :
	sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), gMng::windowName, sf::Style::Close | sf::Style::Titlebar)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initializeView({ 0.0f, 0.0f }, (sf::Vector2f) this->getSize(), gMng::viewZoom);
} // end constr

Graphical_Manager::~Graphical_Manager()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if(pView != NULL)
		delete pView;
} // end destr

void Graphical_Manager::initializeView(sf::Vector2f center, sf::Vector2f windowSize, float zoom)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	pView = new sf::View;
	pView->setCenter(center);
	pView->setSize( windowSize / zoom);
	this->setView(*pView);
} // end initializeView

void Graphical_Manager::execute()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

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
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	pView->setCenter(center);
}

void Graphical_Manager::moveView(sf::Vector2f offset)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	pView->move(offset);
}

void Graphical_Manager::printConsole_log(std::string log)
{
	if(CONSOLE_LOG)
		std::cerr << log << std::endl;
}