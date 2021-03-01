#pragma once

#include <iostream>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

class Window {
private:
	int _width = 0;
	int _height = 0;
	std::string _title = "";

	int _framebufferWidth = 0;
	int _framebufferHeight = 0;

	GLFWwindow* _window = NULL;

	void _initializeGLFW();
	void _initializeInput();
	void _initializeOpenGLVersion();
	void _initializeOpenGLProfile();
	void _initializeGLFWWindow();
	void _initializeFramebufferSize();
	void _initializeGLAD();

	void _readOpenGLGLSLVersion();

	static void _debugCallback(GLenum pSource, GLenum pType, GLuint pID, GLenum pSeverity, GLsizei pLength, const GLchar* pMessage, const void* pParam);
	void _registerDebugMessageCallback();


public:
	Window(int pWidth, int pHeight, std::string pTitle);
	~Window();

	bool isOpen();
	void swapBuffers();
	void pollEvents();
	void terminate();
};
