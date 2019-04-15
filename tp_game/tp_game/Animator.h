#pragma once

//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === Animator Class === //
class Animator
{
private:
	//Frame control
	unsigned int _frameCounter;
	unsigned int _nFrames;

	//Time control
	float _currentTime;
	float _switchTime;

	sf::Sprite* _pSprite;
	sf::IntRect _canvasRect;
	sf::Texture _texture;

public:
	//================================================================//
	// ========== Constructors ========== //
	Animator(std::string texture_filePath, unsigned int nFrames, float switchTime, sf::Sprite* pSprite);
	Animator();
	// ========== Destructors ========== //
	~Animator();

	//================================================================//
	// ========== Initializers ========== //
	void initializeTexture(std::string texture_filePath);

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
private:
	// ========== updateSprite submethods ========== //
	void updateFrame();
	void updateSpriteDirection(bool facingRight);
};