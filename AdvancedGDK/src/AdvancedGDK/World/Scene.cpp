#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Scene.hpp>

namespace agdk
{
///////////////////////////////////////////////////////////////////////////////////////
Scene::Scene()
	: m_autoOrigin{ true }
{
}

///////////////////////////////////////////////////////////////////////////////////////
GlobalObject& Scene::finalizeConstruction(ObjectPtrType< GlobalObject > const& globalObject_)
{
	m_globalObjects.push_back(globalObject_);
	m_objects.push_back(globalObject_.get());

	this->applyNewObjectToOrigin(*globalObject_, m_objects.size());

	return *globalObject_;
}

///////////////////////////////////////////////////////////////////////////////////////
UniversalObject& Scene::finalizeConstruction(ObjectPtrType< UniversalObject > const& universalObject_)
{
	m_universalObjects.push_back(universalObject_);
	m_objects.push_back(universalObject_.get());

	this->applyNewObjectToOrigin(*universalObject_, m_objects.size());

	return *universalObject_;
}

///////////////////////////////////////////////////////////////////////////////////////
PersonalObject& Scene::finalizeConstruction(ObjectPtrType< PersonalObject > const& personalObject_)
{
	m_personalObjects.push_back(personalObject_);
	m_objects.push_back(personalObject_.get());

	this->applyNewObjectToOrigin(*personalObject_, m_objects.size());

	return *personalObject_;
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
	auto delta = location_ - m_origin;
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