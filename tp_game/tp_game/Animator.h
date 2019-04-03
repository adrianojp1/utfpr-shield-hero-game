#pragma once
#include "stdafx.h"

class Animator
{
private:
	//Frame control
	unsigned int _frameCounter;
	unsigned int _nFrames;

	//Time control
	float _currentTime;
	float _switchTime;

	sf::RectangleShape* _pSprite;
	sf::IntRect _canvasRect;
	sf::Texture _texture;

public:
	Animator(std::string texture_filePath, unsigned int nFrames, float switchTime, sf::RectangleShape* pSprite);
	Animator();
	~Animator();

	void initializeTexture(std::string texture_filePath);
	void updateSprite(float* deltaTime, bool facingRight);

	//=============// Sets & Gets //=============//
	//_frameCounter
	void setFrameCounter(unsigned int frameCounter)	{ _frameCounter = frameCounter; }
	unsigned int getSpriteCounter() const			{ return _frameCounter; };
	//_nFrames
	void setnFrames(unsigned int nFrames)			{ _nFrames = nFrames; }
	unsigned int getnFrames() const					{ return _nFrames; }
	//_totalTime
	void setTotalTime(float totalTime)				{ _currentTime = totalTime; }
	float getTotalTime() const						{ return _currentTime; }
	//_switchTime
	void setSwitchTime(float switchTime)			{ _switchTime = switchTime; }
	float getSwitchTime() const						{ return _switchTime; }
	//_pSprite
	void setpSprite(sf::RectangleShape* pSprite)	{ _pSprite = pSprite; }
	sf::RectangleShape* getpSprite() const			{ return _pSprite; }

private:
	//Sprite update modules
	void updateFrame();
	void updateSpriteDirection(bool facingRight);
};