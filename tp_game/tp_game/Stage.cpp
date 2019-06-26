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

Stage::Stage(const int id, const int nPlayers) : Abstract_Entity(id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_currentLevel_index = 0;
	_nPlayers = nPlayers;
	_running = false;

	_nEnemies = (rand() % 11) + 5;
	_nObstacles = (rand() % 11) + 5;
}
Stage::~Stage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	for (Level* pL : _vLevels)
	{
		if (pL)
			delete pL;
	}
	_vLevels.clear();
}

void Stage::initializeLevels(Stage* pStage, int nLevels)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	for (int lv_id = 1; lv_id < nLevels+1; lv_id++)
	{
		std::string tiles_fp = get_lv_fp(_id, lv_id) + gMng::tile_sufix;
		_vLevels.push_back(new Level(tiles_fp, { 0.0f, 0.0f }, pStage));
	}
	//_vLevels[0]->spawnBoss();
}

void Stage::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	check_pauseKey();

	if (!this->isPaused())
	{
		if (_vLevels[_currentLevel_index]->was_finished())
		{
			if (_currentLevel_index < _vLevels.size() - 1)
			{
				goToNextLevel();
			}
			else //Stage finished
			{
				Game::getInstance()->goToNextStage();
			}
		}
		else
		{
			_vLevels[_currentLevel_index]->execute(deltaTime);
		}
	}
}

void Stage::draw()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_vLevels[_currentLevel_index]->draw();
}

void Stage::start()
{
	unpause();
	_running = true;
	_vLevels[_currentLevel_index]->start();
}

void Stage::stop()
{
	_running = false;
}

bool Stage::isRunning()
{
	return _running;
}

void Stage::pause()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	this->desactivate();
}

void Stage::unpause()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_vLevels[_currentLevel_index]->setViewToCenter();
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

void Stage::goToNextLevel()
{
	_currentLevel_index++;
	start_currentLv();
	Game::getInstance()->execute();
}

const std::string Stage::get_stg_fp(const int stg_id) const
{
	return gMng::levels_dir + "Stage_" + std::to_string(stg_id) + "/st" + std::to_string(stg_id);
}

const std::string Stage::get_lv_fp(const int stg_id, const int lv_id) const
{
	return get_stg_fp(stg_id) + "_lv" + std::to_string(lv_id);
}

const int Stage::get_lv_id() const
{
	return _vLevels[_currentLevel_index]->getId();
}

void Stage::set_lv_id(const int lv_id)
{
	_currentLevel_index = lv_id - 1;
}

void Stage::start_currentLv()
{
	_vLevels[_currentLevel_index]->start();
}

