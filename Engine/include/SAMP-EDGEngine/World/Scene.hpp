#pragma once

// Base class headers:
#include <SAMP-EDGEngine/Core/BasicInterfaces/NonCopyable.hpp>

// Stored classes:
#include <SAMP-EDGEngine/World/MapObject.hpp>
#include <SAMP-EDGEngine/World/PersonalObject.hpp>
#include <SAMP-EDGEngine/World/UniversalObject.hpp>
#include <SAMP-EDGEngine/World/GlobalObject.hpp>
#include <SAMP-EDGEngine/World/RemovedBuilding.hpp>

// Core:
#include <SAMP-EDGEngine/Core/Pointers.hpp>

namespace samp_edgengine
{

class ISceneLoader;

/// <summary>
/// Wraps objects inside one scene.
/// </summary>
/// <seealso cref="INonCopyable" />
class Scene
	: public INonCopyable
{
public:
	template <typename TType>
	using ObjectPtrType = SharedPtr<TType>;
	template <typename TType>
	using ObjectContainerType = std::vector< ObjectPtrType<TType> >;

	/// <summary>
	/// Initializes a new instance of the <see cref="Scene"/> class.
	/// </summary>
	Scene();

	/// <summary>
	/// Initializes a new instance of the <see cref="Scene"/> class.
	/// </summary>
	Scene(Scene&&) = default;

	/// <summary>
	/// Move assignment operator.
	/// </summary>
	/// <param name="other_">The other scene.</param>
	/// <returns>Reference to self.</returns>
	Scene& operator=(Scene&& other_) = default;

	/// <summary>
	/// Constructs specified object on the scene.
	/// </summary>
	/// <param name="args_">The construction params.</param>
	/// <returns>Reference to the constructed object..</returns>
	template <typename TType, typename... TArgTypes>
	TType& construct(TArgTypes&&...args_)
	{
		return this->finalizeConstruction(this->beginConstruction<TType>(std::forward<TArgTypes>(args_)...));
	}

	/// <summary>
	/// Begins the object construction (it is not added yet to the scene).
	/// </summary>
	/// <param name="args_">The construction params.</param>
	/// <returns>Owning pointer to the constructed object.</returns>
	template <typename TType, typename... TArgTypes>
	ObjectPtrType<TType> beginConstruction(TArgTypes&&...args_)
	{
		return std::make_shared<TType>(std::forward<TArgTypes>(args_)...);
	}

	/// <summary>
	/// Finalizes the global object construction - adds it to the pool.
	/// </summary>
	/// <param name="globalObject_">The global object.</param>
	/// <returns>Reference to created object.</returns>
	GlobalObject& finalizeConstruction(ObjectPtrType< GlobalObject > const& globalObject_);

	/// <summary>
	/// Finalizes the universal object construction - adds it to the pool.
	/// </summary>
	/// <param name="universalObject_">The universal object.</param>
	/// <returns>Reference to created object.</returns>
	UniversalObject& finalizeConstruction(ObjectPtrType< UniversalObject > const& universalObject_);
	
	/// <summary>
	/// Removes building from the GTA original map.
	/// </summary>
	/// <param name="building_">The building.</param>
	void removeBuilding(RemovedBuilding const building_);
		
	/// <summary>
	/// Cancels the building removal. Does not do anything if called after scene was added to map (it cannot restore removed buildings).
	/// </summary>
	/// <param name="building_">The building.</param>
	void cancelBuildingRemoval(RemovedBuilding const building_);
	
	/// <summary>
	/// Determines whether scene contains the specified object.
	/// </summary>
	/// <param name="object_">The object.</param>
	/// <returns>
	///   <c>true</c> if scene contains the specified object; otherwise <c>false</c>.
	/// </returns>
	bool contains(IMapObject & object_);

	/// <summary>
	/// Sets the origin to specified location.
	/// </summary>
	/// <param name="location_">The location.</param>
	void setOrigin(math::Vector3f const location_);

	/// <summary>
	/// Relocates entire scene to new location. Origin will become point set by `location_`.
	/// </summary>
	/// <param name="location_">The location.</param>
	void setLocation(math::Vector3f const location_);

	/// <summary>
	/// Moves the entire scene by specified delta.
	/// </summary>
	/// <param name="delta_">The delta.</param>
	void move(math::Vector3f const delta_);

	/// <summary>
	/// Sets the automatic origin flag and recalculates origin if set to true.
	/// </summary>
	/// <param name="autoOrigin_">The automatic origin.</param>
	void setAutomaticOrigin(bool const autoOrigin_);

	/// <summary>
	/// Determines whether scene has automatic origin calculation.
	/// </summary>
	/// <returns>
	///   <c>true</c> if has automatic origin; otherwise, <c>false</c>.
	/// </returns>
	bool isAutomaticOrigin() const;

	/// <summary>
	/// Returns the origin.
	/// </summary>
	/// <returns>The origin.</returns>
	math::Vector3f getOrigin() const;
	
	/// <summary>
	/// Returns cref to the objects container (containing non-owining ptrs).
	/// </summary>
	/// <returns>
	///		cref to the objects container (containing non-owining ptrs).
	/// </returns>
	auto const& getObjects() const {
		return m_objects;
	}
	
	/// <summary>
	/// Returns cref to the removed buildings container (containing non-owining ptrs).
	/// </summary>
	/// <returns>
	///		cref to the removed buildings container (containing non-owining ptrs).
	/// </returns>
	auto const& getRemovedBuildings() const {
		return m_removedBuildings;
	}

	friend class MapClass;
private:	
	/// <summary>
	/// Event reaction designed to be called when scene is added to the map.
	/// </summary>
	virtual void whenSceneIsAddedToMap();

	/// <summary>
	/// Event reaction designed to be called when scene is removed from the map.
	/// </summary>
	virtual void whenSceneIsRemovedFromMap();

	/// <summary>
	/// Recalculates the origin.
	/// </summary>
	virtual void recalculateOrigin();
	
	/// <summary>
	/// Applies the new object to origin.
	/// </summary>
	/// <param name="object_">The object.</param>
	void applyNewObjectToOrigin(IMapObject const & object_, std::size_t newObjectsCount_);

	bool									m_insideMap;		// Determines whether this scene is placed inside the map.
	bool									m_autoOrigin;
	math::Vector3f							m_origin;
	std::vector<IMapObject*>				m_objects;
	std::vector<RemovedBuilding>			m_removedBuildings;
	ObjectContainerType< GlobalObject >		m_globalObjects;
	ObjectContainerType< UniversalObject >	m_universalObjects;
};

}
