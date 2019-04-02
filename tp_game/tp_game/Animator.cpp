#include "stdafx.h"
#include "Animator.h"


Animator::Animator(std::string texture_filePath, unsigned int nFrames, float switchTime, sf::RectangleShape* pSprite)
{
	_nFrames = nFrames;
	_switchTime = switchTime;

	_currentTime = 0.0f;
	_frameCounter = 0;

	_pSprite = pSprite;
	initializeTexture(texture_filePath);
}

Animator::Animator()
{
	_nFrames = 0;
	_switchTime = 0;
	_currentTime = 0;
	_frameCounter = 0;
	_pSprite = NULL;
}

Animator::~Animator()
{
}

void Animator::initializeTexture(std::string texture_filePath)
{
	//Load texture 
	if( !_texture.loadFromFile(texture_filePath))
		{ std::cerr << "Failed loading texture: " << texture_filePath << std::endl; }
	
	//Set canvas borders
	_canvasRect.width = _texture.getSize().x / _nFrames;
	_canvasRect.height = _texture.getSize().y;
	_canvasRect.top = 0;

	//Set texture to sprite
	_pSprite->setTexture(&_texture);
}

void Animator::updateSprite(float* deltaTime, bool facingRight)
{
	_currentTime += *deltaTime;

	//Enough time to change the frame
	if (_currentTime >= _switchTime)
	{
		_currentTime -= _switchTime; //Discount the time
		_frameCounter++;

		//The animation is over
		if (_frameCounter >= _nFrames)
			{ _frameCounter = 0; }
	}

	if (facingRight)
	{
		_canvasRect.left = _frameCounter * _canvasRect.width;
		_canvasRect.width = abs(_canvasRect.width);
	}
	else
	{
		_canvasRect.left = (_frameCounter + 1) * abs(_canvasRect.width);
		_canvasRect.width = -abs(_canvasRect.width);
	}

	_pSprite->setTexture(&_texture);
	_pSprite->setTextureRect(_canvasRect);
}