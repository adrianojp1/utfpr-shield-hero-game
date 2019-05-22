//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Timer.h"

Timer::Timer(float totalTime)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_ticking = false;
	_totalTime = totalTime;
	resetTimer();
}

Timer::Timer()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	_ticking = false;
	_totalTime = 0.0f;
	resetTimer();
}

Timer::~Timer()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void Timer::decreaseTime(float deltaTime)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (_ticking)
	{
		_currentTime -= deltaTime;
		{
			if (_currentTime < 0)
			{
				_zeroed = true;
				_ticking = false;
			}
		}
	}
} // end decreaseTime

bool Timer::isTicking() const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _ticking;
} // end isTicking

bool Timer::isZeroed() const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _zeroed;
} // end isZeroed

void Timer::resetTimer()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_currentTime = _totalTime;
	_zeroed = false;
} // end resetTimer

void Timer::pause()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_ticking = false;
} // end pause

void Timer::trigger()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_ticking = true;
} // end trigger

void Timer::reset_and_trigger()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	this->resetTimer();
	this->trigger();
} // end reset_and_trigger

void Timer::setTotalTime(float totalTime)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_totalTime = totalTime;
} // end setTotalTime

float Timer::getTotalTime() const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _totalTime;
} // end getTotalTime

float Timer::getCurrentTime() const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _currentTime;
} // end getCurrentTime
