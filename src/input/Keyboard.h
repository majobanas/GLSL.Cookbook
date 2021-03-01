#pragma once

#include <iostream>

#include <vector>
#include <map>

#include "GLFW/glfw3.h"

class Keyboard {
private:

	static std::map<int, int> _keyboard;
	static std::vector<int> _usedKeys;

	Keyboard();
	~Keyboard();

	static void keyboardCallback(GLFWwindow* pWIndow, int pKey, int pScanmode, int pAction, int pMods);

public:
	static void registerKeyboardCallback(GLFWwindow* pWindow);

	static bool keyDown(int pKey);
	static bool keyPressed(int pKey);
	static bool keyReleased(int pKey);
	static bool keyUp(int pKey);

	static void restartKeys();

};