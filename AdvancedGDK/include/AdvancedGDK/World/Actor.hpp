#pragma once

#include <AdvancedGDK/Core/MathInc.hpp>

namespace agdk
{
using WorldType		= int;
using InteriorType	= int;

/// <summary>
/// Basic interface for every in-game object that has specified its location.
/// </summary>
class IActor
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="IActor"/> class.
	/// </summary>
	IActor() = default;
		
	
	/// <summary>
	/// Finalizes an instance of the <see cref="IActor"/> class.
	/// </summary>
	virtual ~IActor() = default;

	/// <summary>
	/// Sets the location.
	/// </summary>
	/// <param name="location_">The location.</param>
	virtual void setLocation(math::Vector3f const & location_)
	{
		this->syncLocation(location_);
	}

	/// <summary>
	/// Relocates object by the specified delta.
	/// </summary>
	/// <param name="delta_">The delta.</param>
	virtual void move(math::Vector3f const & delta_) {
		this->setLocation(this->getLocation() + delta_);
	}
	
	/// <summary>
	/// Returns actor's location.
	/// </summary>
	/// <returns>Actor's location.</returns>
	virtual math::Vector3f getLocation() const {
		return m_location;
	}

protected:
	
	/// <summary>
	/// Synchronises its actual location with the stored one.
	/// </summary>
	/// <param name="location_">The location.</param>
	void syncLocation(math::Vector3f const & location_)
	{
		m_location = location_;
	}

	math::Vector3f		m_location;	// Last saved location.
	
};
	
/// <summary>
/// Basic interface for every in-game object that has specified its 'w-i-loc'.
/// </summary>
/// <seealso cref="IActor" />
class IWIActor
	: public virtual IActor
{
public:
	
	/// <summary>
	/// Initializes a new instance of the <see cref="IWIActor"/> class.
	/// </summary>
	IWIActor()
		: m_world{ 0 }, m_interior{ 0 }
	{
	}

	/// <summary>
	/// Sets actor's virtual world.
	/// </summary>
	/// <param name="world_">The world.</param>
	virtual void setWorld(WorldType const world_)
	{
		this->syncWorld(world_);
	}

	/// <summary>
	/// Sets actor's interior.
	/// </summary>
	/// <param name="world_">The interior.</param>
	virtual void setInterior(InteriorType const interior_)
	{
		this->syncInterior(interior_);
	}

	/// <summary>
	/// Returns actor's virtual world.
	/// </summary>
	/// <returns>Actor's virtual world.</returns>
	virtual WorldType getWorld() const {
		return m_world;
	}

	/// <summary>
	/// Returns actor's interior.
	/// </summary>
	/// <returns>Actor's interior.</returns>
	virtual InteriorType getInterior() const {
		return m_interior;
	}

protected:
	/// <summary>
	/// Synchronises its actual virtual world with the stored one.
	/// </summary>
	/// <param name="world_">The world.</param>
	virtual void syncWorld(WorldType const world_)
	{
		m_world = world_;
	}

	/// <summary>
	/// Synchronises its actual interior with the stored one.
	/// </summary>
	/// <param name="world_">The interior.</param>
	virtual void syncInterior(InteriorType const interior_)
	{
		m_interior = interior_;
	}

	WorldType			m_world;	// Last saved world.
	InteriorType		m_interior; // Last saved interior.
};

}
