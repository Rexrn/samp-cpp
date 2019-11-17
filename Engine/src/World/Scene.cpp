#include SAMPCPP_PCH

#include <SAMPCpp/World/Scene.hpp>
#include <SAMPCpp/Server/GameMode.hpp>
#include <SAMPCpp/Core/TypesAndDefinitions.hpp>

namespace samp_cpp
{
///////////////////////////////////////////////////////////////////////////////////////
Scene::Scene()
	:
	m_insideMap{ false },
	m_autoOrigin{ true }
{
}

///////////////////////////////////////////////////////////////////////////////////////
GlobalObject& Scene::finalizeConstruction(ObjectPtrType< GlobalObject > const& globalObject_)
{
	m_globalObjects.push_back(globalObject_);
	m_objects.push_back(globalObject_.get());

	this->applyNewObjectToOrigin(*globalObject_, m_objects.size());

	if (m_insideMap)
		GameMode->streamer->whenObjectJoinsMap(*globalObject_);

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
		GameMode->streamer->whenObjectJoinsMap(*universalObject_);

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
		GameMode->streamer->whenObjectJoinsMap(*globalObject);
	}
	for (const_a &universalObject : m_universalObjects) {
		GameMode->streamer->whenObjectJoinsMap(*universalObject);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::whenSceneIsRemovedFromMap()
{
	m_insideMap = false;
	for(const_a &globalObject : m_globalObjects) {
		GameMode->streamer->whenObjectLeavesMap(*globalObject);
	}
	for (const_a &universalObject : m_universalObjects) {
		GameMode->streamer->whenObjectLeavesMap(*universalObject);
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