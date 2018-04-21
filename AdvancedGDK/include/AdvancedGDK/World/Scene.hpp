#pragma once

#include ADVANCEDGDK_PCH

#include <AdvancedGDK/Core/MathInc.hpp>
#include <AdvancedGDK/Core/BasicInterfaces/NonCopyable.hpp>

#include <AdvancedGDK/World/MapObject.hpp>

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
	/// <summary>
	/// Initializes a new instance of the <see cref="Scene"/> class.
	/// </summary>
	Scene();

	/// <summary>
	/// Adds the specified object to the scene.
	/// </summary>
	/// <param name="object_">The object.</param>
	/// <returns>
	///		<c>true</c> if succeeded, otherwise <c>false</c>.
	/// </returns>
	bool add(IMapObject & object_);
	
	/// <summary>
	/// Removes the specified object from the scene.
	/// </summary>
	/// <param name="object_">The object.</param>
	void remove(IMapObject & object_);
	
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

	bool						m_autoOrigin;
	math::Vector3f				m_origin;
	std::vector< IMapObject* >	m_objects;
};

}
