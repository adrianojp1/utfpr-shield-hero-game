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

	_cd_attack.setTotalTime(1.0f);
	_speed = 150.0f;
	_canAttack = true;
	_velocity.x = _speed;
	_attack_offset = sf::Vector2f{ 6.0f, 2.0f } *gMng::textures_scale;
	_attack_rect.setSize(sf::Vector2f{ 12.0f, 4.0f }*gMng::textures_scale);
	_attack_rect.setOrigin(_attack_rect.getSize());
	initialize_animator();
	initialize_AllColliders();

	_overView = *(*_animator)[COMBAT]->getpSprite();
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

	*_animator << new Animation(gMng::orc_idle_texture, 1, 0.0f, 2);
	*_animator << new Animation(gMng::orc_walk_texture, 4, 0.250f, 2);
	*_animator << new Animation(gMng::orc_die_texture, 3, 0.250f, 2);
	*_animator << new Animation(gMng::orc_atk_texture, 3, 0.200f, 2);
} // end initializeAnimators

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

void Orc::doPrincipalOfAttack()
{
	if (_facingRight)
	{
		_attack_rect.setPosition(_position + _attack_offset);
	}
	else
	{
		_attack_rect.setPosition(_position - _attack_offset);
	}
	
	cMng* collMng = cMng::getInstance();
	if (collMng->intersects(_pPlayer1, &_attack_rect))
		_pPlayer1->takeDmg(_attackDamage);
	if (_pPlayer2 && collMng->intersects(_pPlayer2, &_attack_rect))
		_pPlayer2->takeDmg(_attackDamage);
}


void Orc::updateAction(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	
	check_attack();
	if (isAttacking())
	{
		updateAttack();
	}
	else
	{
		_state = WALK;

		int chanceToTurn = 1;//%
		bool decidedToTurn = false;
		if (rand() % 101 < chanceToTurn + 1)
			bool decidedToTurn = true;

		if (!_floor_foward || decidedToTurn)
		{
			turnArround();
		}
		_floor_foward = false;
		moveFoward();
	}
} // end updatePosition
