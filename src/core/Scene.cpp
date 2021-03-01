#include "core/Scene.h"

Scene::Scene()
{
	Light::create(new DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, glm::normalize(glm::vec3(0.0f, -1.0f, -1.0f))));
	//Light::create(new PointLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
	//Light::create(new SpotLight(glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, glm::vec3(-5.0f, 5.0f, 5.0f), 35.0f, 15.0f, glm::normalize(glm::vec3(1.0f, -1.0f, -1.0f))));
	
	// ---------------------------------------------------------------------------------------------------------
	glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 blue = glm::vec3(0.0f, 0.0f, 1.0f);
	// ---------------------------------------------------------------------------------------------------------
	// Forward rendering
	SkyboxMaterial* skyboxMaterial = new SkyboxMaterial("pisa", ".png");
	Object::create(new Object("cube_flat.obj", skyboxMaterial, glm::vec3(0.0f), glm::vec3(100.0f)));
	// ---------------------------------------------------------------------------------------------------------
	Object::create(new Object("plane20x20_2tris_aligned_uvs.obj", new LitMaterial(blue)));
	// ---------------------------------------------------------------------------------------------------------
	/*Object::create(new Object("sphere_smooth.obj", new BasicMaterial(red), glm::vec3(-6.0f, 1.0f, -9.0f)));
	Object::create(new Object("teapot_smooth.obj", new BasicMaterial(green), glm::vec3(-4.0f, 1.0f, -9.0f)));

	Object::create(new Object("suzanna_smooth.obj", new CartoonMaterial(red, 5), glm::vec3(-1.0f, 1.0f, -9.0f)));
	Object::create(new Object("teapot_smooth.obj", new CartoonMaterial(green), glm::vec3(1.0f, 1.0f, -9.0f)));*/

	Object::create(new Object("sphere_smooth.obj", new LitMaterial(red), glm::vec3(-2.0f, 1.0f, 0.0f)));
	Object::create(new Object("teapot_smooth.obj", new LitMaterial(green), glm::vec3(2.0f, 1.0f, 0.0f)));
	// ---------------------------------------------------------------------------------------------------------
	/*Object::create(new Object("suzanna_smooth.obj", new PhongMaterial(red), glm::vec3(-6.0f, 1.0f, -5.0f)));
	Object::create(new Object("teapot_smooth.obj", new PhongMaterial(green), glm::vec3(-4.0f, 1.0f, -5.0f)));

	Object::create(new Object("sphere_smooth.obj", new BlinnMaterial(red), glm::vec3(-1.0f, 1.0f, -5.0f)));
	Object::create(new Object("teapot_smooth.obj", new BlinnMaterial(green), glm::vec3(1.0f, 1.0f, -5.0f)));

	Object::create(new Object("sphere_smooth.obj", new PhysicalMaterial(red, 0.5f, false), glm::vec3(4.0f, 1.0f, -5.0f)));
	Object::create(new Object("teapot_smooth.obj", new PhysicalMaterial(green, 0.5f, true), glm::vec3(6.0f, 1.0f, -5.0f)));
	// ---------------------------------------------------------------------------------------------------------
	Object::create(new Object("sphere_smooth.obj", new TextureMaterial("brick1.jpg"), glm::vec3(-6.0f, 1.0f, -1.0f)));
	Object::create(new Object("teapot_smooth.obj", new TextureMaterial("brick1.jpg"), glm::vec3(-4.0f, 1.0f, -1.0f)));

	Object::create(new Object("sphere_smooth.obj", new TextureBlinnMaterial("brick1.jpg"), glm::vec3(-1.0f, 1.0f, -1.0f)));
	Object::create(new Object("teapot_smooth.obj", new TextureBlinnMaterial("brick1.jpg"), glm::vec3(1.0f, 1.0f, -1.0f)));

	Object::create(new Object("sphere_smooth.obj", new ReflectionCubemapTextureBlinnMaterial(1.0f, "white.png", skyboxMaterial->getTexture()), glm::vec3(4.0f, 1.0f, -1.0f)));
	Object::create(new Object("teapot_smooth.obj", new ReflectionCubemapTextureBlinnMaterial(1.0f, "white.png", skyboxMaterial->getTexture()), glm::vec3(6.0f, 1.0f, -1.0f)));

	Object::create(new Object("sphere_smooth.obj", new RefractionCubemapTextureBlinnMaterial(0.0f, "white.png", skyboxMaterial->getTexture()), glm::vec3(9.0f, 1.0f, -1.0f)));
	Object::create(new Object("teapot_smooth.obj", new RefractionCubemapTextureBlinnMaterial(0.0f, "white.png", skyboxMaterial->getTexture()), glm::vec3(11.0f, 1.0f, -1.0f)));
	// ---------------------------------------------------------------------------------------------------------
	Object::create(new Object("sphere_smooth.obj", new LightsourceCubemapTextureMaterial("white.png", skyboxMaterial->getTexture()), glm::vec3(-6.0f, 1.0f, 3.0f)));
	Object::create(new Object("teapot_smooth.obj", new LightsourceCubemapTextureMaterial("white.png", skyboxMaterial->getTexture()), glm::vec3(-4.0f, 1.0f, 3.0f)));

	Object::create(new Object("cube_flat.obj", new RenderTextureMaterial(Camera::MAIN->getWidth(), Camera::MAIN->getHeight(), Camera::MAIN->getMatrix()), glm::vec3(-1.0f, 1.0f, 3.0f)));
	Object::create(new Object("teapot_smooth.obj", new RenderTextureMaterial(Camera::MAIN->getWidth(), Camera::MAIN->getHeight(), Camera::MAIN->getMatrix()), glm::vec3(1.0f, 1.0f, 3.0f)));
	*/
	Object::create(new Object("sphere_smooth.obj", new EdgeTextureBlinnMaterial(red), glm::vec3(4.0f, 1.0f, 3.0f)));
	Object::create(new Object("teapot_smooth.obj", new EdgeTextureBlinnMaterial(green), glm::vec3(6.0f, 1.0f, 3.0f)));
	
	/*
	// Deferred rendering
	Object::create(new Object("sphere_smooth.obj", new DeferredMaterial("brick1.jpg"), glm::vec3(-3.0f, 0.0f, 0.0f)));
	Object::create(new Object("cube_smooth.obj", new DeferredMaterial("brick1.jpg"), glm::vec3(0.0f, 0.0f, 0.0f)));
	Object::create(new Object("teapot_smooth.obj", new DeferredMaterial("brick1.jpg"), glm::vec3(3.0f, 0.0f, 0.0f)));
	*/
}

Scene::~Scene()
{
}