#pragma once

#include SAMP_EDGENGINE_PCH

#include <SAMP-EDGEngine/Core/TypesAndDefinitions.hpp>

namespace samp_edgengine
{

/// <summary>
/// Basic interface for every in-game 3D object that has its own location.
/// </summary>
class I3DNode
{
public:		
	/// <summary>
	/// Finalizes an instance of the <see cref="I3DNode"/> class.
	/// </summary>
	virtual ~I3DNode() = default;

	/// <summary>
	/// Sets the location.
	/// </summary>
	/// <param name="location_">The new location.</param>
	virtual void setLocation(math::Vector3f const& location_);

	/// <summary>
	/// Relocates object by the specified delta vector.
	/// </summary>
	/// <param name="delta_">The delta vector.</param>
	virtual void move(math::Vector3f const& delta_);

	/// <summary>
	/// Returns nodes location.
	/// </summary>
	/// <returns>Node's location.</returns>
	virtual math::Vector3f getLocation() const;

protected:
	
	/// <summary>
	/// Synchronises stored location with the actual one.
	/// </summary>
	/// <param name="location_">The location.</param>
	void syncLocation(math::Vector3f const& location_);

	math::Vector3f m_storedLocation; // Last saved location.
};


}
