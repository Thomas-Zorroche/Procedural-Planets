#pragma once

#include "glm/glm.hpp"


class NoiseSettings
{
public:
	enum FilterType
	{
		Simple =0,
		Rigid
	};

public:
	NoiseSettings() {};

	float strength() const { return _strength; }
	float baseRoughness() const { return _roughness; }
	float roughness() const { return _baseRoughness; }
	glm::vec3 center() const { return _center; }
	int layersCount() const { return _layersCount; }
	float persistence() const { return _persistence; }
	float minValue() const { return _minValue; }
	FilterType filterType() const { return _filterType; }

	float& strength() { return _strength; }
	float& baseRoughness() { return _baseRoughness; }
	float& roughness() { return _roughness; }
	glm::vec3& center() { return _center; }
	int& layersCount() { return _layersCount; }
	float& persistence() { return _persistence; }
	float& minValue() { return _minValue; }
	FilterType& filterType() { return _filterType; }

private:
	enum FilterType _filterType = FilterType::Simple;
	float _strength = 1.0f;
	float _baseRoughness = 1.0f;
	float _roughness = 2.0f;
	glm::vec3 _center = glm::vec3(0, 0, 0);

	int _layersCount = 1;
	float _persistence = 0.5f; // Amplitude will be half with each layer
	float _minValue = 0.0f;
};