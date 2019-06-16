#pragma once
#include "Skeleton.h"
class BlackSkeleton : public Skeleton
{
private:

public:
	//================================================================//
	// ========== Constructors ========== //
	BlackSkeleton(const sf::Vector2f initPosition);
	BlackSkeleton();
	// ========== Destructors ========== //
	~BlackSkeleton();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators

private:
	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
};

