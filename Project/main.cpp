#include "core/Window.h"
#include "core/Time.h"
#include "core/Camera.h"

#include "core/Renderer.h"
#include "core/ForwardRenderer.h"
#include "core/DeferredRenderer.h"

#include "scenes/myscene.h"

#include "input/Mouse.h"
#include "input/Keyboard.h"

#include "behaviours/CameraControls.h"

int main() {
	int width = 640;
	int height = 480;
	int targetFPS = 1000;
	// ---------------------------------------------------------------------------------------------------------
	Window* window = new Window(width, height, "Cookbook");
	// ---------------------------------------------------------------------------------------------------------
	Camera* camera = new Camera(width, height, 60.f, glm::vec3(0.0f, 5.0f, 10.0f));
	camera->add(new CameraControls(camera));

	Renderer* renderer = new ForwardRenderer(width, height);
	//Renderer* renderer = new DeferredRenderer(width, height);
	MyScene* myScene = new MyScene("MyScene", new Transform(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)));
	myScene->add(camera);
	myScene->populate();


	Time::initialize(1.0 / targetFPS);
	while (window->isOpen()) {
		//std::cout << std::to_string(elapsedTime) << std::endl;
		if (Time::shouldRun()) {
			// Update objects
			myScene->update(Time::getTimePerFrame());
			// Render objects
			renderer->render(myScene);

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

	Light::clear();

	delete renderer;
	renderer = NULL;

	delete myScene;
	myScene = NULL;


	window->terminate();
	delete window;
	window = NULL;

	return 0;
};