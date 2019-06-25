#pragma once
#include "Entity.h"

class Projectile_List;

class Projectile : public Entity
{
private:
	static Projectile_List* _level_proj_list;

	sf::RectangleShape *_collider;

	int _collisionDamage;
	bool _reflected;
public:
	//================================================================//
	// ========== Constructors ========== //
	Projectile(const sf::Vector2f initPosition, const int collDmg, const bool facingRight, const int _id = 0);
	Projectile();
	// ========== Destructors ========== //
	~Projectile();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators

	// ============================================================== =//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);

	//================================================================//
	// ========== Motion ========== //

	virtual void setCollDmg(const int collDmg);
	virtual const int getCollDmg() const;

	virtual void desactivate();

	virtual const bool wasReflected() const;

	virtual void reflect();

	static void setProjList(Projectile_List* projList);
	static Projectile_List* getProjList();
private:
	void updateAction(const float deltaTime);
};

