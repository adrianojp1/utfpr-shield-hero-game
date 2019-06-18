//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Projectile.h"

//======================================================================================================================================//
// === Static initializations === //
const int Projectile::WSproj(0);
const int Projectile::BSproj(1);

Projectile::Projectile(const sf::Vector2f initPosition) :
	Entity(initPosition, true)
{
	_speed = 300.0f;
	_facingRight = false;

	initialize_animator();
	initialize_Collider(_red_proj_collider, (*_animator)[WSproj]->getCanvasSize());
	initialize_Collider(_blue_proj_collider, (*_animator)[BSproj]->getCanvasSize());

}

Projectile::Projectile()
{
	_speed = 0.0f;
}

Projectile::~Projectile()
{
}

void Projectile::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	*_animator << new Animation(gMng::white_skeleton_proj_Sp_Fp, 2, 0.1f); 
	*_animator << new Animation(gMng::black_skeleton_proj_Sp_Fp, 2, 0.1f); 
}

void Projectile::execute(const float deltaTime)
{
	if (this->isActive())
	{
		updateAction(deltaTime);
		updatePosition(deltaTime);
		updateAnime_n_Collider(deltaTime);
	}
}

void Projectile::throw_proj()
{

}

void Projectile::updatePosition(const float deltaTime)
{
	{
		_position += _velocity * deltaTime;
	}
}

void Projectile::updateAction(const float deltaTime)
{
	//if WSkltn
	_current_collider = _red_proj_collider;
	_animator->setCurrentAnime(WSproj);

	//if BSkltn
	//_animator->setCurrentAnime(BSproj);

	if (isFacingRight())
		_velocity.x = _speed;
	else
		_velocity.x = -_speed;
}

void Projectile::updateAnime_n_Collider(const float deltaTime)
{
	_animator->updateAnimation(deltaTime, _facingRight);
	_current_collider->setPosition(_position);
}