#pragma once
#include "Skeleton.h"

class Projectile;

class White_Skeleton : public Skeleton
{
private:

public:
	//================================================================//
	// ========== Constructors ========== //
	White_Skeleton(const sf::Vector2f initPosition);
	White_Skeleton();
	// ========== Destructors ========== //
	~WhiteSkeleton();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators

	int getProj_id();
private:
	// ========== execute submethods ========== //
}; 

