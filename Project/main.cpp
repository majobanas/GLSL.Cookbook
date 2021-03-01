#include "core/Window.h"
#include "core/Time.h"
#include "core/Camera.h"

#include "core/Renderer.h"
#include "core/ForwardRenderer.h"
#include "core/DeferredRenderer.h"

#include "core/Scene.h"

#include "input/Mouse.h"
#include "input/Keyboard.h"



int main() {
	int width = 640;
	int height = 480;
	int targetFPS = 10000;
	// ---------------------------------------------------------------------------------------------------------
	Window* window = new Window(width, height, "Cookbook");
	// ---------------------------------------------------------------------------------------------------------
	Camera* camera = new Camera(width, height, 60.f, glm::vec3(0.0f, 5.0f, 10.0f));

	Renderer* renderer = new ForwardRenderer(width, height);
	//Renderer* renderer = new DeferredRenderer(width, height);
	Scene* scene = new Scene();

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Time::initialize(1.0 / targetFPS);
	while (window->isOpen()) {
		//std::cout << std::to_string(elapsedTime) << std::endl;
		if (Time::shouldRun()) {
			// Update objects
			camera->update(Time::getTimePerFrame());
			// Render objects
			renderer->render(scene);
			// Apply graphics
			window->swapBuffers();
			// Receive input
			Mouse::restartButtons();
			Keyboard::restartKeys();
			window->pollEvents();
			Time::reset();
		}
	}

	Camera::clear();

	Shader::clear();
	Mesh::clear();
	Texture::clear();

	Object::clear();
	Light::clear();

	delete renderer;
	renderer = NULL;

	delete scene;
	scene = NULL;


	window->terminate();
	delete window;
	window = NULL;

	return 0;
};