#pragma once
#include "Entity.h"
#include "WhiteSkeleton.h"
#include "BlackSkeleton.h"

class Projectile : public Entity
{
private:
	sf::RectangleShape *_red_proj_collider; //WSkltn projectile
	sf::RectangleShape *_blue_proj_collider; //BSkltn projectile

	//================================================================//
	//======================== Static Consts =========================//
	static const int WSproj;
	static const int BSproj;

public:
	//================================================================//
	// ========== Constructors ========== //
	Projectile(const sf::Vector2f initPosition);
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
	virtual void throw_proj();
	virtual void updatePosition(const float deltaTime);
	virtual void updateAnime_n_Collider(const float deltaTime);


private:
	void updateAction(const float deltaTime);
};

