#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

#include "engine/ProceduralEditor.hpp"
#include "engine/Log.hpp"
#include "engine/Window.hpp"
#include "engine/Scene.hpp"
#include "engine/Color.hpp"

#include "editor/AppLog.hpp"

namespace proceduralPlanet 
{
	class Planet;

	enum class ObserverFlag
	{
		RESOLUTION = 0,
		COLOR,
		MESH
	};
};

namespace editor 
{

void mainloop(Window& windowObject);

enum class UpdateMode
{
	Auto = 0,
	OnRelease,
	OnGenerate
};



class Application
{
public:
	Application(int argc, char** argv);
	~Application() {};

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	static Application& Get() { return *s_instance; }
public:
	void ClearColor() const;

	// Updates Handler
	void GenerateUpdateQueue(bool onRelease = false);
	void Update(proceduralPlanet::ObserverFlag flag);
	void AddUpdateIntoQueue(proceduralPlanet::ObserverFlag flag);
	UpdateMode& GetUpdateMode() { return _updateMode; }
	UpdateMode GetUpdateMode() const { return _updateMode; }

	Window& GetWindow() { return *_window; }
	ProceduralEditor& GetEditor() { return *_editor; }
	std::shared_ptr<proceduralPlanet::Planet> GetPlanet() { return _planet; }

	void AppendPlanet(const std::shared_ptr<proceduralPlanet::Planet>& planet) { _planet = planet; }

	Color GetBackgroundColor() const { return _backgroundColor; }
	Color& GetBackgroundColor() { return _backgroundColor; }

	float GetLastFrameDuration() const { return _lastFrameDuration; }
	void SetLastFrameDuration(float time) { _lastFrameDuration = time; }

	bool GetLoading() const { return _loading; }

	bool IsReadyToGenerate() const { return _readyToGenerate; }
	void SetReadyToGenerate(bool ready) { _readyToGenerate = ready; }

	void AppendLog(const char* str) { _log.AddLog(("[%05d] " + std::string(str) + "\n").c_str(), ImGui::GetFrameCount()); }
	void DrawLog() { _log.Draw(); }

private:
	static Application* s_instance;

private:
	std::unique_ptr<Window> _window = nullptr;
	std::unique_ptr<ProceduralEditor> _editor = nullptr;
	std::shared_ptr<proceduralPlanet::Planet> _planet = nullptr;

	UpdateMode _updateMode = UpdateMode::Auto;
	std::vector<proceduralPlanet::ObserverFlag> _updatesQueue;

	Color _backgroundColor = Color(0.570, 0.598, 0.727);

	float _lastFrameDuration = 0.0f;

	bool _loading = false;
	bool _readyToGenerate = false; // TODO : remove this

	AppLog _log;
};

} // ns Editor


