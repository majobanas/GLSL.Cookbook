#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "GLFW/glfw3.h"

#include "glm/glm.hpp"

class Mouse {
private:

	static GLFWwindow* _window;

	static std::map<int, int> _mouse;
	static std::vector<int> _usedButtons;

	static glm::vec2 _position;
	static glm::vec2 _previousPosition;
	static glm::vec2 _lockPosition;

	Mouse();
	~Mouse();

	static void mouseMoveCallback(GLFWwindow* pWindow, double pX, double pY);
	static void mouseButtonCallback(GLFWwindow* pWindow, int pButton, int pAction, int pMods);

public:
	static void registerMouseMoveCallback(GLFWwindow* pWindow);
	static void registerMouseButtonCallback(GLFWwindow* pWindow);

	static bool buttonDown(int pButton);
	static bool buttonPressed(int pButton);
	static bool buttonReleased(int pButton);
	static bool buttonUp(int pButton);

	static void restartButtons();

	static glm::vec2 getPosition();
	static glm::vec2 getPreviousPosition();
	static glm::vec2 getPositionDifference();
	static glm::vec2 getLockPosition();

	static void setPosition(glm::vec2 pPosition);
	static void setLockPosition(glm::vec2 pPosition);

	static void hide();
	static void show();
};
