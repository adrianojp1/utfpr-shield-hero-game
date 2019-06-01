//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Animation.h"

//======================================================================================================================================//
// === Classes headers for definition === //
#include "Graphical_Manager.h"

//======================================================================================================================================//
// === Animation Methods === //
Animation::Animation(const std::string texture_filePath, unsigned int nFrames, float switchTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_nFrames = nFrames;
	_switchTime = switchTime;

	_currentTime = 0.0f;
	_frameCounter = 0;

	initialize(texture_filePath);
}

Animation::Animation()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	_nFrames = 0;
	_switchTime = 0;
	_currentTime = 0.0f;
	_frameCounter = 0;
}

Animation::~Animation()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void Animation::initialize(std::string texture_filePath)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	gMng::load_n_setTexture(&_sprite, texture_filePath, &_texture);

	sf::Vector2u textureSize = _texture.getSize();

	//Set canvas borders
	_canvasRect.width = (int)(textureSize.x / _nFrames);
	_canvasRect.height = (int)(textureSize.y);
	_canvasRect.top = 0;

	_sprite.setSize(this->getCanvasSize());
	_sprite.setOrigin(_sprite.getSize() / 2.0f);
	_sprite.setTexture(&_texture);
}

void Animation::updateAnimation(float deltaTime, bool facingRight)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_currentTime += deltaTime;

	updateFrame();
	updateCanvasDirection(facingRight);

	_sprite.setTextureRect(_canvasRect);
}

void Animation::setFrameCounter(unsigned int frameCounter)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_frameCounter = frameCounter;
}

unsigned int Animation::getFrameCounter() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _frameCounter;
}

void Animation::setnFrames(unsigned int nFrames)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_nFrames = nFrames;
}

unsigned int Animation::getnFrames() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _nFrames;
}

void Animation::setCurrentTime(float currentTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_currentTime = currentTime;
}

float Animation::getCurrentTime() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _currentTime;
}

void Animation::setSwitchTime(float switchTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_switchTime = switchTime;
}

float Animation::getSwitchTime() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _switchTime;
}

sf::RectangleShape* Animation::getpSprite()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return &_sprite;
}

sf::Vector2f Animation::getCanvasSize() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return sf::Vector2f((float)_canvasRect.width, (float)_canvasRect.height);
}

bool Animation::isFinished() const
{
	return (getFrameCounter() == getnFrames() - 1);
}

void Animation::reset()
{
	setFrameCounter(0);
}

void Animation::updateFrame()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//Enough time to change the frame
	if (_currentTime >= _switchTime)
	{
		_currentTime -= _switchTime; //Discount the time
		_frameCounter++;

		//The animation is over
		if (_frameCounter >= _nFrames)
		{
			_frameCounter = 0;
		}
	}
} // end updateFrame

void Animation::updateCanvasDirection(bool facingRight)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

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
} // end updateSpriteDirection