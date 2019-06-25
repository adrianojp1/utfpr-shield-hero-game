//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Projectile.h"

#include "Projectile_List.h"
Projectile_List* Projectile::_level_proj_list = NULL;

//======================================================================================================================================//
// === Static initializations === //

Projectile::Projectile(const sf::Vector2f initPosition, const int collDmg, const bool facingRight, const int _id) :
	Entity(initPosition, true, _id)
{
	_speed = 20.0f;
	_facingRight = facingRight;
	_collisionDamage = collDmg;
	_reflected = false;

	initialize_animator();
	initialize_Collider(_collider, (*_animator)[0]->getCanvasSize());
	_current_collider = _collider;

	_level_proj_list->includeProjectile(this);
}

Projectile::Projectile()
{
	_collisionDamage = 0;
	_reflected = false;
}

Projectile::~Projectile()
{
	_level_proj_list->remove_projectile(this);
	if (_animator)
		delete _animator;
	if (_collider)
		delete _collider;
}

void Projectile::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	switch (_id)
	{
	case 0: //White_Skeleton
		*_animator << new Animation(gMng::white_skeleton_proj_texture, 2, 0.1f, 2);
		break;

	case 1: //Black_Skeleton
		*_animator << new Animation(gMng::black_skeleton_proj_texture, 2, 0.1f, 2);
		break;

	case 2: //Dispenser
		*_animator << new Animation(gMng::energy_ball_texture, 1, 0.0f, 1);
		break;

	default:
		break;
	}

	_animator->setCurrentAnime(0);
}

void Projectile::execute(const float deltaTime)
{
	_velocity.x = 0.0f;

	if (this->isActive())
	{
		checkColls();

		updateAction(deltaTime);
		updatePosition(deltaTime);

		resetColls();
	}
}

void Projectile::setCollDmg(const int collDmg)
{
	_collisionDamage = collDmg;
}

const int Projectile::getCollDmg() const
{
	return _collisionDamage;
}

void Projectile::desactivate()
{
	_active = false;
	//_current_collider->setPosition(3000.0f, 3000.0f);
}

const bool Projectile::wasReflected() const
{
	return _reflected;
}

void Projectile::reflect()
{
	turnArround();
	_reflected = true;
	_animator->getCurrentAnime()->getpSprite()->setFillColor(sf::Color(120, 255, 0));
}

void Projectile::setProjList(Projectile_List* projList)
{
	_level_proj_list = projList;
}

Projectile_List* Projectile::getProjList()
{
	return _level_proj_list;
}

void Projectile::updateAction(const float deltaTime)
{
	moveFoward();
}