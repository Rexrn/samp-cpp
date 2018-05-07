#pragma once

#include ADVANCEDGDK_PCH

#include <AdvancedGDK/Core/MathInc.hpp>
#include <AdvancedGDK/Core/BasicInterfaces/NonCopyable.hpp>

#include <AdvancedGDK/World/MapObject.hpp>
#include <AdvancedGDK/World/MapObject/PersonalObject.hpp>
#include <AdvancedGDK/World/MapObject/UniversalObject.hpp>
#include <AdvancedGDK/World/MapObject/GlobalObject.hpp>

namespace agdk
{

/// <summary>
/// Wraps objects inside one scene.
/// </summary>
/// <seealso cref="INonCopyable" />
class Scene final
	: public INonCopyable
{
public:	
	template <typename TType>
	using ObjectPtrType			= std::shared_ptr<TType>;
	template <typename TType>
	using ObjectContainerType	= std::vector< ObjectPtrType<TType> >;

	/// <summary>
	/// Initializes a new instance of the <see cref="Scene"/> class.
	/// </summary>
	Scene();

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
	/// Finalizes the personal object construction - adds it to the pool.
	/// </summary>
	/// <param name="personalObject_">The personal object.</param>
	/// <returns>Reference to created object.</returns>
	PersonalObject& finalizeConstruction(ObjectPtrType< PersonalObject > const& personalObject_);

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
	void setAutomaticOrigin(bool const autoOrigin_)
	{
		if (autoOrigin_ && !m_autoOrigin)
			this->recalculateOrigin();

		m_autoOrigin = autoOrigin_;
	}
			
	/// <summary>
	/// Determines whether scene has automatic origin calculation.
	/// </summary>
	/// <returns>
	///   <c>true</c> if has automatic origin; otherwise, <c>false</c>.
	/// </returns>
	bool isAutomaticOrigin() const {
		return m_autoOrigin;
	}

	/// <summary>
	/// Returns the origin.
	/// </summary>
	/// <returns>The origin.</returns>
	math::Vector3f getOrigin() const {
		return m_origin;
	}

private:	
	/// <summary>
	/// Recalculates the origin.
	/// </summary>
	void recalculateOrigin();
	
	/// <summary>
	/// Applies the new object to origin.
	/// </summary>
	/// <param name="object_">The object.</param>
	void applyNewObjectToOrigin(IMapObject const & object_, std::size_t newObjectsCount_);

	bool									m_autoOrigin;
	math::Vector3f							m_origin;
	std::vector<IMapObject*>				m_objects;
	ObjectContainerType< GlobalObject >		m_globalObjects;
	ObjectContainerType< UniversalObject >	m_universalObjects;
	ObjectContainerType< PersonalObject >	m_personalObjects;
};

}
