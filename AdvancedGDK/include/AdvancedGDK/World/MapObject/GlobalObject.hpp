#pragma once

#include ADVANCEDGDK_PCH

#include <AdvancedGDK/World/MapObject.hpp>
#include <AdvancedGDK/World/Actor.hpp>

namespace agdk
{

class GlobalObject
	:
	public IMapObject,
	public IActor
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="GlobalObject"/> class.
	/// </summary>
	GlobalObject();

	/// <summary>
	/// Finalizes an instance of the <see cref="PersonalObject"/> class.
	/// </summary>
	virtual ~GlobalObject();
	
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
	virtual void setModel(std::int32_t const modelIndex_) override;

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
	/// Returns the object handle.
	/// </summary>
	/// <returns>The object handle.</returns>
	std::int32_t getHandle() const {
		return m_handle;
	}

	/// <summary>
	/// Determines whether this instance is spawned.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this instance is spawned; otherwise, <c>false</c>.
	/// </returns>
	bool isSpawned() const {
		return this->getHandle() != INVALID_OBJECT_ID;
	}
private:
	
	/// <summary>
	/// Applies the text material.
	/// </summary>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="textMaterial_">The text material.</param>
	/// <param name="player_">The player.</param>
	virtual void applyText(std::size_t const materialIndex_, Text const & textMaterial_, [[maybe_unused]] Player const * player_ = nullptr) override;
	
	/// <summary>
	/// Applies the texture.
	/// </summary>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="textureMaterial_">The texture material.</param>
	/// <param name="player_">The player.</param>
	virtual void applyTexture(std::size_t const materialIndex_, Texture const & textureMaterial_, [[maybe_unused]] Player const * player_ = nullptr) override;

	std::int32_t	m_handle;
};

}
