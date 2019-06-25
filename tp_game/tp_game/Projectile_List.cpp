#include "stdafx.h"
#include "Projectile_List.h"

Projectile_List::Projectile_List()
{
}

Projectile_List::~Projectile_List()
{
	clear();
}

Projectile_List::iterator Projectile_List::begin()
{
	return _proj_list.begin();
}

Projectile_List::iterator Projectile_List::end()
{
	return _proj_list.end();
}

void Projectile_List::clear()
{
	_proj_list.clear();
}

void Projectile_List::includeProjectile(Projectile* pJ)
{
	if (pJ)
		_proj_list.push_back(pJ);
}

void Projectile_List::execute_projectiles(const float deltaTime)
{
	for (Projectile* pJ : *this)
	{
		pJ->execute(deltaTime);
	}
}

void Projectile_List::update_drawables()
{
	for (Projectile* pJ : *this)
	{
		pJ->updateAnime_n_Collider();
	}
}

void Projectile_List::draw_projectiles()
{
	for (Projectile* pJ : *this)
	{
		pJ->draw();
	}
}

void Projectile_List::remove_projectile(Projectile* pP)
{
	_proj_list.remove(pP);
}

