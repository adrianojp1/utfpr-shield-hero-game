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
Animation::Animation(sf::Texture* pTexture, unsigned int nFrames, float switchTime, int nRows) : 
	_switchTimer(switchTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_nRows = nRows;
	_nFrames = nFrames;
	_frameCounter = 0;
	initialize(pTexture);

	_switchTimer.trigger();
}

Animation::Animation()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	_nFrames = 0;
	_frameCounter = 0;
}

Animation::~Animation()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void Animation::initialize(sf::Texture* pTexture)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_sprite.setTexture(pTexture);

	setCanvasSize(sf::Vector2u{ (pTexture->getSize().x / _nFrames), pTexture->getSize().y / _nRows});
	initializeSprite();
}

void Animation::initializeSprite()
{
	_sprite.setScale(gMng::textures_scale);
	_sprite.setSize(this->getCanvasSize());
	_sprite.setOrigin(_sprite.getSize() / 2.0f);
	_sprite.setTextureRect(getCanvasRect());
}

void Animation::updateAnimation(bool facingRight)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	
	updateFrame();
	updateCanvas(facingRight);

	_sprite.setTextureRect(_canvasRect);
}

void Animation::updateAnimation()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	updateFrame();

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
	_switchTimer.setCurrentTime(currentTime);
}

float Animation::getCurrentTime() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _switchTimer.getCurrentTime();
}

void Animation::setSwitchTime(float switchTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_switchTimer.setTotalTime(switchTime);
}

float Animation::getSwitchTime() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _switchTimer.getTotalTime();
}

sf::RectangleShape* Animation::getpSprite()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return &_sprite;
}

void Animation::setCanvasRect(sf::IntRect rect)
{
	_canvasRect = rect;
}

sf::IntRect Animation::getCanvasRect()
{
	return _canvasRect;
}

void Animation::setCanvasSize(const sf::Vector2u size)
{
	_canvasRect.height = size.y;
	_canvasRect.width = size.x;
}

sf::Vector2f Animation::getCanvasSize() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return sf::Vector2f((float)_canvasRect.width, (float)_canvasRect.height);
}

bool Animation::isGoingToChangeFrame() const
{
	return (_switchTimer.getCurrentTime() - *_switchTimer.getDeltaTime()) < 0;
}

bool Animation::isRunning()
{
	return _switchTimer.isTicking();
}

bool Animation::isFinished()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if ((getFrameCounter() == (getnFrames() - 1)) && isGoingToChangeFrame())
	{
		_switchTimer.reset_and_trigger();
		resetFrameCounter();
		return true;
	}
	return false;
}

void Animation::resetFrameCounter()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	setFrameCounter(0);
}

void Animation::updateFrame()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	const float remanescentTime = _switchTimer.getCurrentTime() - *_switchTimer.getDeltaTime();

	//Enough time to change the frame
	if (isGoingToChangeFrame())
	{
		_switchTimer.setCurrentTime(_switchTimer.getTotalTime() + remanescentTime);
		_frameCounter++;

		//The animation is over
		if (_frameCounter >= _nFrames)
		{
			this->resetFrameCounter();
		}
	}
	else
	{
		_switchTimer.decreaseTime();
	}
} // end updateFrame

void Animation::updateCanvas(bool facingRight)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (_nRows == 2)
	{
		_canvasRect.left = _frameCounter * _canvasRect.width;
		if (facingRight)
		{
			_canvasRect.top = 0;
		}
		else
		{
			_canvasRect.top = _canvasRect.height;
		}
	}
	else
	{
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
	}
	
} // end updateSpriteDirection