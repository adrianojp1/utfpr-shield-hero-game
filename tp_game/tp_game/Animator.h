#pragma once

//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === Classes Headers === //
#include "Animation.h"

//======================================================================================================================================//
// === Classes Declaration === //
class Entity;

//======================================================================================================================================//
// === Animator Class === //
class Animator
{
private:
	Entity* _pEntity;

	std::vector<Animation*> _vAnimes;
	Animation* _currentAnime;
public:
	//================================================================//
	// ========== Constructors ========== //
	Animator(Entity* pEntity);
	Animator();
	// ========== Destructors ========== //
	virtual ~Animator();

	//================================================================//
	// ========== Initializers ========== //

	//================================================================//
	// ========== Loop methods ========== //
	void updateAnimation(bool facingRight);

	//================================================================//
	// ========== Sets & Gets ========== //
	//_currentAnime
	void setCurrentAnime(const int i);
	Animation* getCurrentAnime() const;
	//================================================================//
	// ========== Animations methods ========== //
	virtual void add_anime(Animation* pAnim);
	virtual void operator<<(Animation* pAnim);
	virtual Animation* operator[](int i);
};