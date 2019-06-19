//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Stage.h"

//======================================================================================================================================//
// === Classes headers for definition === //
#include "Game.h"

//======================================================================================================================================//
// === Stage methods === //

Stage::Stage() : Abstract_Entity()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_currentScenarioId = 0;
	initializeStage();
}
Stage::~Stage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	_currentScenarioId = 0;
}

void Stage::initializeStage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	
	_vScenarios.push_back(new Scenario);
}

void Stage::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	check_pauseKey();

	if(!this->isPaused())
		_vScenarios[_currentScenarioId]->execute(deltaTime);
}

void Stage::draw()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_vScenarios[_currentScenarioId]->draw();
}

void Stage::pause()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	this->desactivate();
}

void Stage::unpause()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	this->activate();
}

bool Stage::isPaused()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return !this->isActive();
}

void Stage::check_pauseKey()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (pauseKey_isPressed())
	{
		this->pause();
	}
}

bool Stage::pauseKey_isPressed()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
}