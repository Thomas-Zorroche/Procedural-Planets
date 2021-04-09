#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

#include "engine/Log.hpp"
#include "engine/Window.hpp"
#include "engine/Scene.hpp"

void mainloop(Window& windowObject);

class Planet;

enum class UpdateMode
{
	Auto = 0,
	OnRelease,
	OnGenerate
};

enum class ObserverFlag
{
	RESOLUTION = 0,
	COLOR,
	RADIUS,
	NOISE,
	LAYER
};

class Application
{
public:
	Application(const std::shared_ptr<Planet>& planet);
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	// Updates Handler
	void GenerateUpdateQueue(bool onRelease = false);
	void Update(ObserverFlag flag);
	void AddUpdateIntoQueue(ObserverFlag flag);
	UpdateMode& GetUpdateMode() { return _updateMode; }
	UpdateMode GetUpdateMode() const { return _updateMode; }

	// Wireframe Mode
	bool IsWireframeMode() const;
	void SetWireframeMode(bool mode);
	bool& GetWireframeModePtr();

	std::shared_ptr<Planet> PlanetPtr();

private:
	std::shared_ptr<Planet> _planet;
	
	bool _wireframeMode = false;
	
	UpdateMode _updateMode = UpdateMode::Auto;
	std::vector<ObserverFlag> _updatesQueue;
};

