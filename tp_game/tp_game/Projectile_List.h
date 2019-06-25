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
	std::list<Projectile*> _proj_list;
public:
	Projectile_List();
	virtual ~Projectile_List();

	typedef std::list<Projectile*>::iterator iterator;

	iterator begin();
	iterator end();

	void clear();
	void includeProjectile(Projectile* pP);
	void execute_projectiles(const float deltaTime);
	void update_drawables();
	//void removeTile(Tile* pT);
	void draw_projectiles();
	void remove_projectile(Projectile* pP);
	void delete_projectiles();
};

