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

	*_animator << new Animation(gMng::orc_idle_texture, 1, 0.0f);
	*_animator << new Animation(gMng::orc_walk_texture, 4, 0.250f);
	*_animator << new Animation(gMng::orc_die_texture, 3, 0.250f);
	*_animator << new Animation(gMng::orc_atk_texture, 3, 0.200f);
} // end initializeAnimators


void Orc::attack()
{
	_velocity.x = 0.0f;
	_state = COMBAT;
}

void Orc::turnArround()
{
	_facingRight ? _facingRight = false : _facingRight = true;
}

void Orc::colliding_onLeft()
{
	_velocity.x = 0.0f;
	turnArround();
}

void Orc::colliding_onRight()
{
	_velocity.x = 0.0f;
	turnArround();
}


void Orc::updateAction(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	
	_state = WALK;

	srand(static_cast<unsigned int>(time(NULL)));
	int chanceToTurn = 5;//%
	bool decidedToTurn = false;
	if (rand() % 101 < chanceToTurn + 1)
		bool decidedToTurn = true;

	if (!_floor_foward || decidedToTurn)
	{
		turnArround();
	}
	_floor_foward = false;
	moveFoward();
	

} // end updatePosition
