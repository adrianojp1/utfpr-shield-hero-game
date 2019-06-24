//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Dynamic_Spike.h"

//======================================================================================================================================//
// === Static initializations === //

//======================================================================================================================================//
// === Dynamic_Spike methods === //

Dynamic_Spike::Dynamic_Spike(const sf::Vector2f initPosition, const int id) :
	Static_Spike(initPosition, id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_collisionDamage = 1;
	_cd_action.setTotalTime(2.0f);
	_cd_action.trigger();
	_speed = 150.0f;

	_hidden_position = { _position.x, _position.y + _realSize.y };
}

Dynamic_Spike::Dynamic_Spike() : Static_Spike()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");
	_collider = NULL;
}

Dynamic_Spike::~Dynamic_Spike()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (_collider)
		delete _collider;
	if (_animator)
		delete _animator;
}

void Dynamic_Spike::updateAction(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_velocity.y = 0.0f;

	if (_cd_action.isZeroed())
	{
		if (_triggered)
		{
			if (_position.y < _hidden_position.y - _realSize.y)
			{
				_cd_action.reset_and_trigger();
				_position.y = _hidden_position.y - _realSize.y;
				_triggered = false;
			}
			else
			{
				_velocity.y -= _speed;
			}
		}
		else
		{
			if (_position.y > _hidden_position.y)
			{
				_cd_action.reset_and_trigger();
				_position.y = _hidden_position.y;
				_triggered = true;
			}
			else
			{
				_velocity.y += _speed;
			}
		}
	}
}