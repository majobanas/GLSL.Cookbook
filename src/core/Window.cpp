#include "core/Window.h"

#include "input/Mouse.h"
#include "input/Keyboard.h"

void Window::_initializeGLFW()
{
	if (!glfwInit()) {
		std::cerr << "Unable to initialize GLFW!" << std::endl;
		//exit(EXIT_FAILURE);
	}
}

void Window::_initializeOpenGLVersion()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
}

void Window::_initializeOpenGLProfile()
{
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    bool debug = true;
    if (debug) {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }
    int samples = 0;
    if (samples > 0) {
        glfwWindowHint(GLFW_SAMPLES, samples);
    }
}

void Window::_initializeGLFWWindow()
{
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    _window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
    if (!_window) {
        std::cerr << "Unable to create GLFWwindow." << std::endl;
        glfwTerminate();
        //exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(_window);
}

void Window::_initializeInput()
{
    Mouse::registerMouseMoveCallback(_window);
    Mouse::registerMouseButtonCallback(_window);

    Keyboard::registerKeyboardCallback(_window);
}

void Window::_initializeFramebufferSize()
{
    glfwGetFramebufferSize(_window, &_framebufferWidth, &_framebufferHeight);
    //std::cout << std::to_string(_framebufferWidth) + " " + std::to_string(_framebufferHeight) << std::endl;
}

void Window::_initializeGLAD()
{
    if (!gladLoadGL()) {
        std::cerr << "Unable to initialize GLAD!" << std::endl;
        //exit(EXIT_FAILURE);
    }
}

void Window::_readOpenGLGLSLVersion()
{
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Renderer: %s\n", renderer);
    printf("GL Vendor: %s\n", vendor);
    printf("GL Version (string): %s\n", version);
    printf("GL Version (integer): %d.%d\n", major, minor);
    printf("GLSL Version: %s\n", glslVersion);
}

void Window::_debugCallback(GLenum pSource, GLenum pType, GLuint pID, GLenum pSeverity, GLsizei pLength, const GLchar* pMessage, const void* pParam)
{
    printf("%s:%s[%s] (%d) : %s\n", pSource, pType, pSeverity, pID, pMessage);
}

void Window::_registerDebugMessageCallback()
{
    glDebugMessageCallback(_debugCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
}

bool Window::isOpen()
{
    return (!glfwWindowShouldClose(_window) && !glfwGetKey(_window, GLFW_KEY_ESCAPE));
}

void Window::swapBuffers()
{
    glfwSwapBuffers(_window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::terminate()
{
    glfwTerminate();
}

Window::Window(int pWidth, int pHeight, std::string pTitle)
    : _width(pWidth), _height(pHeight), _title(pTitle)
{
    _initializeGLFW();
    _initializeOpenGLVersion();
    _initializeOpenGLProfile();
    _initializeGLFWWindow();
    _initializeInput();
    _initializeFramebufferSize();
    _initializeGLAD();

    _readOpenGLGLSLVersion();

    //_registerDebugMessageCallback(); // Throws error
}

Window::~Window()
{
}
