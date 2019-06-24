//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Ghost_Tile.h"

//======================================================================================================================================//
// === Static initializations === //

//======================================================================================================================================//
// === Ghost_Tile methods === //

Ghost_Tile::Ghost_Tile(const sf::Vector2f initPosition, const int id) :
	Obstacle(initPosition, id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initialize_animator();
	initialize_Collider(_collider, (*_animator)[0]->getCanvasSize());

	_current_collider = _collider;
	_current_collider->setPosition(_position);

	_cd_action.setTotalTime(4.0f);
}

Ghost_Tile::Ghost_Tile() : Obstacle()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");
	_collider = NULL;
}

Ghost_Tile::~Ghost_Tile()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (_collider)
		delete _collider;
	if (_animator)
		delete _animator;
}

void Ghost_Tile::colliding_onTop()
{
	_triggered = true;
	_cd_action.trigger();
}

void Ghost_Tile::activ_ghost()
{
	_animator->getCurrentAnime()->getpSprite()->setFillColor(sf::Color(255, 255, 255, 100));
}

void Ghost_Tile::deactiv_ghost()
{
	_animator->getCurrentAnime()->getpSprite()->setFillColor(sf::Color(255, 255, 255, 255));
}

void Ghost_Tile::updateAction(const float deltaTime)
{
	if (!_cd_action.isTicking())
	{
		if (_coll_onTop)
		{
			_cd_action.reset_and_trigger();
		}
	}
	else
	{
		if (_cd_action.getCurrentTime() < 3.0f)
			activ_ghost();
		else
			deactiv_ghost();
	}
}

