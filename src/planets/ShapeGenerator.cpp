#include "ShapeGenerator.hpp"

#include "ShapeSettings.hpp"
#include "noise/NoiseFilter.hpp"

ShapeGenerator::ShapeGenerator(const std::shared_ptr<ShapeSettings>& shapeSettings)
	: _settings(shapeSettings), 
	_noiseFilters(std::vector<std::shared_ptr<NoiseFilter> >(_settings->noiseLayers().size(), nullptr))
{

}

glm::vec3 ShapeGenerator::calculatePointOnPlanet(const glm::vec3& pointOnUnitSphere) const
{
	float firstLayerValue = 0;
	float elevation = 0;

	if (_noiseFilters.size() > 0)
	{
		firstLayerValue = _noiseFilters[0]->evaluate(pointOnUnitSphere);
		if (_settings->noiseLayer(0)->enabled())
		{
			elevation = firstLayerValue;
		}
	}

	for (size_t i = 1; i < _noiseFilters.size(); i++)
	{
		if (_settings->noiseLayer(i)->enabled())
		{
			float mask = (_settings->noiseLayer(i)->useFirstLayerAsMask()) ? firstLayerValue : 1;
			elevation += _noiseFilters[i]->evaluate(pointOnUnitSphere) * mask;
		}
	}
	return pointOnUnitSphere * _settings->planetRadius() * (1 + elevation);
}

void ShapeGenerator::addFilter(const std::shared_ptr<NoiseFilter>& layer)
{
	_noiseFilters.push_back(layer);
}

void ShapeGenerator::removeLastFilter()
{
	_noiseFilters.pop_back();
}

void ShapeGenerator::removeFilter(unsigned int index)
{
	_noiseFilters.erase(_noiseFilters.begin() + index);
}
