#include "input/Keyboard.h"

std::map<int, int> Keyboard::_keyboard = 
{  
	{GLFW_KEY_UNKNOWN, -1},
	{GLFW_KEY_ESCAPE, -1},
	{GLFW_KEY_F1, -1},
	{GLFW_KEY_F2, -1},
	{GLFW_KEY_F3, -1},
	{GLFW_KEY_F4, -1},
	{GLFW_KEY_F5, -1},
	{GLFW_KEY_F6, -1},
	{GLFW_KEY_F7, -1},
	{GLFW_KEY_F8, -1},
	{GLFW_KEY_F9, -1},
	{GLFW_KEY_F10, -1},
	{GLFW_KEY_F11, -1},
	{GLFW_KEY_F12, -1},

	{GLFW_KEY_GRAVE_ACCENT, -1},
	{GLFW_KEY_1, -1},
	{GLFW_KEY_2, -1},
	{GLFW_KEY_3, -1},
	{GLFW_KEY_4, -1},
	{GLFW_KEY_5, -1},
	{GLFW_KEY_6, -1},
	{GLFW_KEY_7, -1},
	{GLFW_KEY_8, -1},
	{GLFW_KEY_9, -1},
	{GLFW_KEY_0, -1},
	{GLFW_KEY_MINUS, -1},
	{GLFW_KEY_EQUAL, -1},
	{GLFW_KEY_BACKSPACE, -1},
	
	{GLFW_KEY_TAB, -1},
	{GLFW_KEY_Q, -1},
	{GLFW_KEY_W, -1},
	{GLFW_KEY_E, -1},
	{GLFW_KEY_R, -1},
	{GLFW_KEY_T, -1},
	{GLFW_KEY_Y, -1},
	{GLFW_KEY_U, -1},
	{GLFW_KEY_I, -1},
	{GLFW_KEY_O, -1},
	{GLFW_KEY_P, -1},
	{GLFW_KEY_LEFT_BRACKET, -1},
	{GLFW_KEY_RIGHT_BRACKET, -1},
	
	{GLFW_KEY_CAPS_LOCK, -1},
	{GLFW_KEY_A, -1},
	{GLFW_KEY_S, -1},
	{GLFW_KEY_D, -1},
	{GLFW_KEY_F, -1},
	{GLFW_KEY_G, -1},
	{GLFW_KEY_H, -1},
	{GLFW_KEY_J, -1},
	{GLFW_KEY_K, -1},
	{GLFW_KEY_L, -1},
	{GLFW_KEY_SEMICOLON, -1},
	{GLFW_KEY_APOSTROPHE, -1},
	{GLFW_KEY_BACKSLASH, -1},
	{GLFW_KEY_ENTER, -1},
	
	{GLFW_KEY_LEFT_SHIFT, -1},
	{GLFW_KEY_Z, -1},
	{GLFW_KEY_X, -1},
	{GLFW_KEY_C, -1},
	{GLFW_KEY_V, -1},
	{GLFW_KEY_B, -1},
	{GLFW_KEY_N, -1},
	{GLFW_KEY_M, -1},
	{GLFW_KEY_COMMA, -1},
	{GLFW_KEY_PERIOD, -1},
	{GLFW_KEY_SLASH, -1},
	{GLFW_KEY_RIGHT_SHIFT, -1},

	{GLFW_KEY_LEFT_CONTROL, -1},
	{GLFW_KEY_LEFT_ALT, -1},
	{GLFW_KEY_SPACE, -1},
	{GLFW_KEY_RIGHT_ALT, -1},
	{GLFW_KEY_RIGHT_CONTROL, -1},

	{GLFW_KEY_DELETE, -1},
	{GLFW_KEY_PAUSE, -1},
	{GLFW_KEY_PRINT_SCREEN, -1},
	{GLFW_KEY_HOME, -1},

	{GLFW_KEY_NUM_LOCK, -1},
	{GLFW_KEY_KP_DIVIDE, -1},
	{GLFW_KEY_KP_MULTIPLY, -1},
	{GLFW_KEY_KP_SUBTRACT, -1},

	{GLFW_KEY_KP_7, -1},
	{GLFW_KEY_KP_8, -1},
	{GLFW_KEY_KP_9, -1},

	{GLFW_KEY_KP_4, -1},
	{GLFW_KEY_KP_5, -1},
	{GLFW_KEY_KP_6, -1},
	{GLFW_KEY_KP_ADD, -1},

	{GLFW_KEY_KP_1, -1},
	{GLFW_KEY_KP_2, -1},
	{GLFW_KEY_KP_3, -1},

	{GLFW_KEY_UP, -1},
	{GLFW_KEY_KP_0, -1},
	{GLFW_KEY_KP_DECIMAL, -1},
	{GLFW_KEY_KP_ENTER, -1},

	{GLFW_KEY_LEFT, -1},
	{GLFW_KEY_DOWN, -1},
	{GLFW_KEY_RIGHT, -1}
};

std::vector<int> Keyboard::_usedKeys = std::vector<int>();

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::keyboardCallback(GLFWwindow* pWIndow, int pKey, int pScanmode, int pAction, int pMods)
{
	_keyboard[pKey] = pAction;
	_usedKeys.push_back(pKey);
}

void Keyboard::registerKeyboardCallback(GLFWwindow* pWindow)
{
	glfwSetKeyCallback(pWindow, keyboardCallback);
}

bool Keyboard::keyDown(int pKey)
{
	return _keyboard[pKey] == GLFW_REPEAT;
}

bool Keyboard::keyPressed(int pKey)
{
	return _keyboard[pKey] == GLFW_PRESS;
}

bool Keyboard::keyReleased(int pKey)
{
	return _keyboard[pKey] == GLFW_RELEASE;
}

bool Keyboard::keyUp(int pKey)
{
	return _keyboard[pKey] == -1;
}

void Keyboard::restartKeys()
{
	for (auto& key : _usedKeys) {
		if (_keyboard[key] == GLFW_PRESS) {
			_keyboard[key] = GLFW_REPEAT;
		}
		if (_keyboard[key] != GLFW_REPEAT) {
			_keyboard[key] = -1;
		}
	}
	_usedKeys.clear();
}
