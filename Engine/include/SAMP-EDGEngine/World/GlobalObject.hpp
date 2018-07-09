#pragma once

#include SAMP_EDGENGINE_PCH

// Base class header:
#include <SAMP-EDGEngine/World/MapObject.hpp>

// Other headers:
#include <SAMP-EDGEngine/Core/BasicInterfaces/PlacementTracker.hpp>

namespace samp_edgengine
{

class GlobalObject
	:
	public IMapObject
{
public:	
	friend class ServerClass;

	/// <summary>
	/// Initializes a new instance of the <see cref="GlobalObject"/> class.
	/// </summary>
	GlobalObject();

	/// <summary>
	/// Finalizes an instance of the <see cref="PersonalObject"/> class.
	/// </summary>
	virtual ~GlobalObject();
	
	// Tracking:	
	/// <summary>
	/// Sets the placement tracker.
	/// </summary>
	/// <param name="tracker_">The tracker.</param>
	void setPlacementTracker(IGlobalObjectPlacementTracker *tracker_);

	/// <summary>
	/// Returns the placement tracker.
	/// </summary>
	/// <returns>Placement tracker</returns>
	IGlobalObjectPlacementTracker* getPlacementTracker() const;

	/// <summary>
	/// Spawns this object in world.
	/// </summary>
	bool spawn();
	
	/// <summary>
	/// Despawns this object from world.
	/// </summary>
	void despawn();

	/// <summary>
	/// Sets the object model.
	/// </summary>
	/// <param name="modelIndex_">Index of the model.</param>
	virtual void setModel(Int32 const modelIndex_) override;

	/// <summary>
	/// Sets the object location.
	/// </summary>
	/// <param name="location_">The location.</param>
	virtual void setLocation(math::Vector3f const & location_) override;

	/// <summary>
	/// Sets the object rotation.
	/// </summary>
	/// <param name="rotationAxes_">The rotation axes.</param>
	virtual void setRotation(math::Vector3f const & rotationAxes_) override;

	/// <summary>
	/// Returns the object location.
	/// </summary>
	/// <returns>The object location.</returns>
	virtual math::Vector3f getLocation() const override;

	/// <summary>
	/// Returns the object rotation.
	/// </summary>
	/// <returns>The object rotation.</returns>
	virtual math::Vector3f getRotation() const override;
	
	/// <summary>
	/// Returns the global object placement.
	/// </summary>
	/// <returns>Global object placement</returns>
	GlobalObjectPlacement getPlacement() const;

	/// <summary>
	/// Returns the object handle.
	/// </summary>
	/// <returns>The object handle.</returns>
	Int32 getHandle() const;

	/// <summary>
	/// Determines whether this instance is spawned.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is spawned; otherwise, <c>false</c>.
	/// </returns>
	bool isSpawned() const;

	/// <summary>
	/// Returns object type.
	/// </summary>
	/// <returns>
	///		Type of the object.
	/// </returns>
	virtual Type getType() const override {
		return Type::Global;
	}
private:
	
	// Tracking:	
	/// <summary>
	/// Sends the placement update to the tracker.
	/// </summary>
	void sendPlacementUpdate();

	/// <summary>
	/// Applies the text material.
	/// </summary>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="textMaterial_">The text material.</param>
	/// <param name="player_">The player.</param>
	virtual void applyText(std::size_t const materialIndex_, Text const & textMaterial_, [[maybe_unused]] Player const * player_) override;
	
	/// <summary>
	/// Applies the texture.
	/// </summary>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="textureMaterial_">The texture material.</param>
	/// <param name="player_">The player.</param>
	virtual void applyTexture(std::size_t const materialIndex_, Texture const & textureMaterial_, [[maybe_unused]] Player const * player_) override;

	Int32 m_handle;

	IGlobalObjectPlacementTracker* m_placementTracker;
};

}
