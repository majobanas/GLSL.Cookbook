#include "core/Time.h"

Time::Time()
{
}

Time::~Time()
{
}

double Time::_timePerFrame = 0.0;

void Time::initialize(double pTimePerFrame)
{
	_timePerFrame = pTimePerFrame;
	glfwSetTime(0.0);
}

bool Time::shouldRun()
{
	return getDelta() >= _timePerFrame;
}

void Time::reset()
{
	glfwSetTime(getDelta() - _timePerFrame);
}

double Time::getTimePerFrame()
{
	return _timePerFrame;
}

double Time::getDelta()
{
	return glfwGetTime();
}
