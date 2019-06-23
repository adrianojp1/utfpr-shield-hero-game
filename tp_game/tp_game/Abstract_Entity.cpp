//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Abstract_Entity.h"

//======================================================================================================================================//
// === Classes headers for definition === //
#include "Player.h"

//======================================================================================================================================//
// === Static initializations === //
Graphical_Manager* Abstract_Entity::_pGraphMng = NULL;

Player* Abstract_Entity::_pPlayer1 = NULL;
Player* Abstract_Entity::_pPlayer2 = NULL;

//======================================================================================================================================//
// === Entity methods === //
Abstract_Entity::Abstract_Entity(const sf::Vector2f initPosition, const bool active, const int id)
{
	_position = initPosition;
	_active = active;
	_id = id;
}

Abstract_Entity::Abstract_Entity(const int id, const sf::Vector2f initPosition, const bool active)
{
	_position = initPosition;
	_active = active;
	_id = id;
}

Abstract_Entity::Abstract_Entity()
{
	_position = { 0.0f, 0.0f };
	_active = false;
}

Abstract_Entity::~Abstract_Entity()
{
}


void Abstract_Entity::setPosition(const sf::Vector2f position)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_position = position;
}

sf::Vector2f Abstract_Entity::getPosition() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _position;
}


void Abstract_Entity::activate()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_active = true;
}

void Abstract_Entity::desactivate()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_active = false;
}

bool Abstract_Entity::isActive() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	return _active;
}

void Abstract_Entity::setGraphManager(gMng* gMng)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_pGraphMng = gMng;
}

gMng* Abstract_Entity::getGraphManager()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	return _pGraphMng;
}

void Abstract_Entity::setpPlayer1(Player* pP1)
{
	if(!_pPlayer1)
		_pPlayer1 = pP1;
}

Player* Abstract_Entity::getpPlayer1()
{
	return _pPlayer1;
}

void Abstract_Entity::setpPlayer2(Player* pP2)
{
	if (!_pPlayer2)
		_pPlayer2 = pP2;
}

Player* Abstract_Entity::getpPlayer2()
{
	return _pPlayer2;
}

void Abstract_Entity::setId(const int id)
{
	_id = id;
}

const int Abstract_Entity::getId()
{
	return _id;
}
