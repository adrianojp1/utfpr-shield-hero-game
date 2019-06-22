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

	srand(static_cast<unsigned int>(time(NULL)));
	_nEnemies = (rand() % 11) + 5;
	_nObstacles = (rand() % 11) + 5;

	//levels_dir + stage2_dir + stg2_prefix + "id" + pos_sufix;
	int lv_id = 1;
	int stg_id = 2;
	std::string pos_fp = get_lv_fp(stg_id, lv_id) + gMng::pos_sufix;
	std::string tiles_fp = get_lv_fp(stg_id, lv_id) + gMng::tile_sufix;

	_vScenarios.push_back(new Level(pos_fp, tiles_fp, { -400.0f, -300.0f }, _nEnemies, _nObstacles));
}

void Stage::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	check_pauseKey();

	if (!this->isPaused())
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

const std::string Stage::get_stg_fp(const int stg_id) const
{
	return gMng::levels_dir + "Stage_" + std::to_string(stg_id) + "/st" + std::to_string(stg_id);
}

const std::string Stage::get_lv_fp(const int stg_id, const int lv_id) const
{
	return get_stg_fp(stg_id) + "_lv" + std::to_string(lv_id);
}