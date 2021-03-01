#include "input/Mouse.h"

GLFWwindow* Mouse::_window = NULL;

std::map<int, int> Mouse::_mouse =
{
	{GLFW_MOUSE_BUTTON_LEFT, -1},
	{GLFW_MOUSE_BUTTON_MIDDLE, -1},
	{GLFW_MOUSE_BUTTON_RIGHT, -1}
};

std::vector<int> Mouse::_usedButtons = std::vector<int>();

glm::vec2 Mouse::_position = glm::vec2(0.0f);
glm::vec2 Mouse::_previousPosition = glm::vec2(0.0f);
glm::vec2 Mouse::_lockPosition = glm::vec2(0.0f);


Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::mouseMoveCallback(GLFWwindow* pWindow, double pX, double pY)
{
	_previousPosition = _position;
	_position = glm::vec2(pX, pY);
}

void Mouse::mouseButtonCallback(GLFWwindow* pWindow, int pButton, int pAction, int pMods)
{
	_mouse[pButton] = pAction;
	_usedButtons.push_back(pButton);
}

void Mouse::registerMouseMoveCallback(GLFWwindow* pWindow)
{
	if (_window == NULL) {
		_window = pWindow;
	}

	glfwSetCursorPosCallback(pWindow, mouseMoveCallback);
	//setPosition(glm::vec2(0.0f, 0.0f));
}

void Mouse::registerMouseButtonCallback(GLFWwindow* pWindow)
{
	if (_window == NULL) {
		_window = pWindow;
	}
	glfwSetMouseButtonCallback(pWindow, mouseButtonCallback);
}

bool Mouse::buttonDown(int pButton)
{
	return _mouse[pButton] == GLFW_REPEAT;
}

bool Mouse::buttonPressed(int pButton)
{
	return _mouse[pButton] == GLFW_PRESS;
}

bool Mouse::buttonReleased(int pButton)
{
	return _mouse[pButton] == GLFW_RELEASE;
}

bool Mouse::buttonUp(int pButton)
{
	return _mouse[pButton] == -1;
}

void Mouse::restartButtons()
{
	for (auto& button : _usedButtons) {
		if (_mouse[button] == GLFW_PRESS) {
			_mouse[button] = GLFW_REPEAT;
		}
		if (_mouse[button] != GLFW_REPEAT) {
			_mouse[button] = -1;
		}
	}
	_usedButtons.clear();
}

glm::vec2 Mouse::getPosition()
{
	return _position;
}

glm::vec2 Mouse::getPreviousPosition()
{
	return _previousPosition;
}

glm::vec2 Mouse::getPositionDifference()
{
	return _position - _previousPosition;
}

glm::vec2 Mouse::getLockPosition()
{
	return _lockPosition;
}

void Mouse::setPosition(glm::vec2 pPosition)
{
	glfwSetCursorPos(_window, pPosition.x, pPosition.y);
	_position = pPosition;
	_previousPosition = pPosition;
}

void Mouse::setLockPosition(glm::vec2 pPosition)
{
	_lockPosition = pPosition;
}

void Mouse::hide()
{
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Mouse::show()
{
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
