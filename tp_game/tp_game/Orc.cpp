//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Orc.h"

//======================================================================================================================================//
// === Orc methods === //

Orc::Orc(const sf::Vector2f initPosition) :
	Enemy(initPosition)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	cd_attack.setTotalTime(1.0f);
	_speed = 150.0f;
	_canAttack = true;
	_velocity.x = _speed;

	initialize_animator();
	initialize_AllColliders();

} // end constr (parameters)

Orc::Orc() :
	Enemy()
{
	_speed = 0.0f;
}

Orc::~Orc()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_animator)
		delete _animator;
} // end destr



void Orc::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	*_animator << new Animation(gMng::orc_idle_Sp_Fp, 1, 0.0f);
	*_animator << new Animation(gMng::orc_walk_Sp_Fp, 4, 0.250f);
	*_animator << new Animation(gMng::orc_die_Sp_Fp, 3, 0.250f);
	*_animator << new Animation(gMng::orc_atk_Sp_Fp, 3, 0.200f);
} // end initializeAnimators

void Orc::attack()
{
}

void Orc::turnArround()
{
	_velocity.x = -_velocity.x;
}

void Orc::collision_onLeft()
{
	turnArround();
}

void Orc::collision_onRight()
{
	turnArround();
}

bool Orc::isAttacking() const
{
	return _attacking;
}


void Orc::updateAction(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	
	

	if (_velocity.x != 0.0f)
	{
		_state = WALK;
	}
	else if (_velocity.x == 0.0f) //to change
	{
		_state = IDLE;
	}

	

} // end updatePosition
