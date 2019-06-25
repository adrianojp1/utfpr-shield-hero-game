#pragma once
#include "Skeleton.h"

class Black_Skeleton : public Skeleton
{
private:

public:
	//================================================================//
	// ========== Constructors ========== //
	Black_Skeleton(const sf::Vector2f initPosition);
	Black_Skeleton();
	// ========== Destructors ========== //
	~Black_Skeleton();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators
	int getProj_id();
private:
	// ========== execute submethods ========== //
};

