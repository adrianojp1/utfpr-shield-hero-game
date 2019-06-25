#pragma once
#include "Skeleton.h"

class Projectile;

class WhiteSkeleton : public Skeleton
{
private:

public:
	//================================================================//
	// ========== Constructors ========== //
	WhiteSkeleton(const sf::Vector2f initPosition);
	WhiteSkeleton();
	// ========== Destructors ========== //
	~WhiteSkeleton();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators

	int getProj_id();
private:
	// ========== execute submethods ========== //
}; 

