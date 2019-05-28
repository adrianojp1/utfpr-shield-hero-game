#pragma once

//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === Classes Declaration === //
class Entity;

//======================================================================================================================================//
// === Animator Class === //
class Animator
{
private:
	//Visual members
	sf::Sprite* _pSprite;
	sf::IntRect _canvasRect;
	sf::Texture _texture;

	//Frame members
	unsigned int _frameCounter;
	unsigned int _nFrames;

	//Time members
	float _currentTime;
	float _switchTime;

	Entity* _pEntity;

public:
	//================================================================//
	// ========== Constructors ========== //
	Animator(std::string texture_filePath, unsigned int nFrames, float switchTime, Entity* pEntity);
	Animator();
	// ========== Destructors ========== //
	virtual ~Animator();

	//================================================================//
	// ========== Initializers ========== //
	void initializeTexture(std::string texture_filePath);
	void initializeSprite();

	//================================================================//
	// ========== Loop methods ========== //
	void updateSprite(float deltaTime, bool facingRight);

	//================================================================//
	// ========== Sets & Gets ========== //
	//_frameCounter
	void setFrameCounter(unsigned int frameCounter);
	unsigned int getSpriteCounter() const;
	//_nFrames
	void setnFrames(unsigned int nFrames);
	unsigned int getnFrames() const;
	//_currentTime
	void setCurrentTime(float currentTime);
	float getCurrentTime() const;
	//_switchTime
	void setSwitchTime(float switchTime);
	float getSwitchTime() const;
	//_pSprite
	void setpSprite(sf::Sprite* pSprite);
	sf::Sprite* getpSprite() const;	
	//spriteSize
	sf::Vector2f getSpriteSize() const;
private:
	// ========== updateSprite submethods ========== //
	void updateFrame();
	void updateSpriteDirection(bool facingRight);
};