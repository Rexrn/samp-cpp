#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Scene.hpp>
#include <AdvancedGDK/Server/GameMode.hpp>
#include <AdvancedGDK/Core/TypesAndDefinitions.hpp>
#include <AdvancedGDK/World/SceneLoader.hpp>

namespace agdk
{
///////////////////////////////////////////////////////////////////////////////////////
Scene::Scene()
	:
	m_insideMap{ false },
	m_autoOrigin{ true }
{
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::loadFromStream(std::istream& stream_, ISceneLoader const& loader_)
{
	loader_.loadFromStream(*this, stream_);
}

///////////////////////////////////////////////////////////////////////////////////////
GlobalObject& Scene::finalizeConstruction(ObjectPtrType< GlobalObject > const& globalObject_)
{
	m_globalObjects.push_back(globalObject_);
	m_objects.push_back(globalObject_.get());

	this->applyNewObjectToOrigin(*globalObject_, m_objects.size());

	if (m_insideMap)
		GameMode->Streamer->whenObjectJoinsMap(*globalObject_);

	return *globalObject_;
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::removeBuilding(RemovedBuilding const building_)
{
	m_removedBuildings.push_back(building_);
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::cancelBuildingRemoval(RemovedBuilding const building_)
{
	auto it = std::find(m_removedBuildings.begin(), m_removedBuildings.end(), building_);
	if ( it != m_removedBuildings.end() )
	{
		m_removedBuildings.erase(it);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
UniversalObject& Scene::finalizeConstruction(ObjectPtrType< UniversalObject > const& universalObject_)
{
	m_universalObjects.push_back(universalObject_);
	m_objects.push_back(universalObject_.get());

	this->applyNewObjectToOrigin(*universalObject_, m_objects.size());

	if (m_insideMap)
		GameMode->Streamer->whenObjectJoinsMap(*universalObject_);

	return *universalObject_;
}

///////////////////////////////////////////////////////////////////////////////////////
bool Scene::contains(IMapObject & object_)
{
	return std::find(m_objects.begin(), m_objects.end(), &object_) != m_objects.end();
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::setOrigin(math::Vector3f const location_)
{
	m_autoOrigin	= false;
	m_origin		= location_;
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::setLocation(math::Vector3f const location_)
{
	const_a delta = location_ - m_origin;
	for (auto object : m_objects)
		object->move(delta);

	m_origin = location_;
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::move(math::Vector3f const delta_)
{
	this->setLocation(m_origin + delta_);
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::setAutomaticOrigin(bool const autoOrigin_)
{
	if (autoOrigin_ && !m_autoOrigin)
		this->recalculateOrigin();

	m_autoOrigin = autoOrigin_;
}

///////////////////////////////////////////////////////////////////////////////////////
bool Scene::isAutomaticOrigin() const
{
	return m_autoOrigin;
}

///////////////////////////////////////////////////////////////////////////////////////
math::Vector3f Scene::getOrigin() const
{
	return m_origin;
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::whenSceneIsAddedToMap()
{
	m_insideMap = true;
	for (const_a &globalObject : m_globalObjects) {
		GameMode->Streamer->whenObjectJoinsMap(*globalObject);
	}
	for (const_a &universalObject : m_universalObjects) {
		GameMode->Streamer->whenObjectJoinsMap(*universalObject);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::whenSceneIsRemovedFromMap()
{
	m_insideMap = false;
	for(const_a &globalObject : m_globalObjects) {
		GameMode->Streamer->whenObjectLeavesMap(*globalObject);
	}
	for (const_a &universalObject : m_universalObjects) {
		GameMode->Streamer->whenObjectLeavesMap(*universalObject);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::recalculateOrigin()
{
	m_origin.set(0, 0, 0);

	for (auto object : m_objects)
		m_origin += object->getLocation();
	
	m_origin /= static_cast<float>(m_objects.size());
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::applyNewObjectToOrigin(IMapObject const & object_, std::size_t newObjectsCount_)
{
	m_origin *= static_cast<float>( newObjectsCount_ - 1 );
	m_origin += object_.getLocation();
	m_origin /= static_cast<float>( newObjectsCount_ );
}

} // namespace agdk