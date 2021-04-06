#pragma once

#include <string>
#include <memory>

#include "ini.h"

class Planet;

class IOManager
{
public:
	static IOManager& get()
	{
		static IOManager instance;
		return instance;
	}

	IOManager(const IOManager&) = delete;
	IOManager& operator=(const IOManager&) = delete;

	void save(const std::string& outputFileName);
	bool open(const std::string& inputFileName, std::shared_ptr<Planet>& planet);

private:
	void loadValues(const mINI::INIStructure& ini, std::shared_ptr<Planet>& planet);

	IOManager() = default;
	~IOManager() = default;
};