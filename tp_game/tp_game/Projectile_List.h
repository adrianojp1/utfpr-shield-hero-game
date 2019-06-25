#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Projectile.h"
#include "List.h"

//======================================================================================================================================//
// === Projectile_List Class === //
class Projectile_List
{
private:
	List<Projectile*> _proj_list;
public:
	Projectile_List();
	virtual ~Projectile_List();

	typedef List<Projectile*>::iterator iterator;

	iterator begin();
	iterator end();

	void clear();
	void includeProjectile(Projectile* pJ);
	void execute_projectiles(const float deltaTime);
	void update_drawables();
	//void removeTile(Tile* pT);
	void draw_projectiles();
};

