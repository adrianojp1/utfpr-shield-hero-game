//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Dispenser.h"

//======================================================================================================================================//
// === Static initializations === //
Projectile_List* Dispenser::_level_proj_list = NULL;

//======================================================================================================================================//
// === Dispenser methods === //
Dispenser::Dispenser(const sf::Vector2f initPosition, const bool facingRight, const int id) :
	Obstacle(initPosition, id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_facingRight = facingRight;
	if (_facingRight)
	{
		_id++;
		_proj_initPos = _position + (sf::Vector2f{ 9.0f, 0.0f } *gMng::textures_scale);
	}
	else
	{
		_proj_initPos = _position - (sf::Vector2f{ 9.0f, 0.0f } *gMng::textures_scale);
	}

	initialize_animator();
	initialize_Collider(_collider, (*_animator)[0]->getCanvasSize());

	_current_collider = _collider;
	_current_collider->setPosition(_position);

	_cd_action.setTotalTime(10.0f);
	_cd_action.trigger();
}

Dispenser::Dispenser() : Obstacle()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");
	_collider = NULL;
}

Dispenser::~Dispenser()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (_collider)
		delete _collider;
	if (_animator)
		delete _animator;
}

void Dispenser::setProjList(Projectile_List* projList)
{
	_level_proj_list = projList;
}

Projectile_List* Dispenser::getProjList()
{
	return _level_proj_list;
}

void Dispenser::spit_ball()
{
	Projectile* pProj = new Projectile(_proj_initPos, 1, _facingRight, 2);
	pProj->setSpeed(100.0f);
	_level_proj_list->includeProjectile(pProj);
}

void Dispenser::updateAction(const float deltaTime)
{
	if (_cd_action.isZeroed())
	{
		spit_ball();
		_cd_action.reset_and_trigger();
	}
}

