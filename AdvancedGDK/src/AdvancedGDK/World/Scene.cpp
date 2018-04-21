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
bool Scene::add(IMapObject & object_)
{
	auto it = std::find(m_objects.begin(), m_objects.end(), &object_);
	if (it == m_objects.end())
	{
		if (m_autoOrigin)
		{
			m_origin *= static_cast<float>(m_objects.size());
			m_origin += object_.getLocation();
			m_origin /= static_cast<float>(m_objects.size() + 1);
		}
		
		m_objects.emplace_back(&object_);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::remove(IMapObject & object_)
{
	auto it = std::find(m_objects.begin(), m_objects.end(), &object_);
	if (it != m_objects.end())
	{
		if (m_autoOrigin)
		{
			m_origin *= static_cast<float>(m_objects.size());
			m_origin -= object_.getLocation();
			m_origin /= static_cast<float>(m_objects.size() - 1);
		}
		
		m_objects.erase(it);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
bool Scene::contains(IMapObject & object_)
{
	return std::find(m_objects.begin(), m_objects.end(), &object_) != m_objects.end();
}

///////////////////////////////////////////////////////////////////////////////////////
void Scene::setOrigin(math::Vector3f const location_)
{
	m_autoOrigin = false;
	m_origin = location_;
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

} // namespace agdk