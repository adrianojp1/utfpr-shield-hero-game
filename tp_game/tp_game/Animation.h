#pragma once
//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === Animation Class === //
class Animation
{
private:
	//Visual members
	sf::Texture _texture;
	sf::RectangleShape _sprite;
	sf::IntRect _canvasRect;

	//Frame members
	unsigned int _frameCounter;
	unsigned int _nFrames;

	//Time members
	float _currentTime;
	float _switchTime;

public:
	//================================================================//
	// ========== Constructors ========== //
	Animation(const std::string texture_filePath, unsigned int nFrames, float switchTime);
	Animation();

	// ========== Destructors ========== //
	virtual ~Animation();

	//================================================================//
	// ========== Initializers ========== //
	void initialize(std::string texture_filePath);

	//================================================================//
	// ========== Loop methods ========== //
	void updateAnimation(float deltaTime, bool facingRight);

	//================================================================//
	// ========== Sets & Gets ========== //
	//_frameCounter
	void setFrameCounter(unsigned int frameCounter);
	unsigned int getFrameCounter() const;
	//_nFrames
	void setnFrames(unsigned int nFrames);
	unsigned int getnFrames() const;
	//_currentTime
	void setCurrentTime(float currentTime);
	float getCurrentTime() const;
	//_switchTime
	void setSwitchTime(float switchTime);
	float getSwitchTime() const;
	//_sprite
	sf::RectangleShape* getpSprite();
	//canvasSize
	sf::Vector2f getCanvasSize() const;

	bool isFinished() const;
	void reset();
private:
	// ========== updateSprite submethods ========== //
	void updateFrame();
	void updateCanvasDirection(bool facingRight);
};

typedef Animation Anime;