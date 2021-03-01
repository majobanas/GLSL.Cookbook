#pragma once
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>

class Time {
private:
	Time();
	~Time();

	static double _timePerFrame;
public:
	static void initialize(double pTimePerFrame);

	static bool shouldRun();
	static void reset();

	static double getTimePerFrame();
	static double getDelta();
};