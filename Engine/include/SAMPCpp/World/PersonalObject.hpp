#pragma once
#include SAMPCPP_PCH



// Base class header:
#include <SAMPCpp/World/PerPlayerObject.hpp>

namespace samp_cpp
{

/// <summary>
/// An object that is visible only to its owner. Its only owner is the player himself.
/// </summary>
/// <seealso cref="PerPlayerObject" />
class PersonalObject
	: public PerPlayerObject
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="PersonalObject"/> class.
	/// </summary>
	/// <param name="player_">The player.</param>
	PersonalObject(Player const & player_);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="PersonalObject"/> class.
	/// </summary>
	virtual ~PersonalObject();

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
	/// Returns the object handle.
	/// </summary>
	/// <returns>The object handle.</returns>
	Int32 getHandle() const;

	/// <summary>
	/// Returns the player the object belongs to.
	/// </summary>
	/// <returns>The player the object belongs to.</returns>
	Player const& getPlayer() const;

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
		return Type::Personal;
	}
private:

	/// <summary>
	/// Applies the text.
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

	/// <summary>
	/// Returns the distance squared to specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <returns></returns>
	virtual math::Meters getDistanceSquaredTo(Player const & player_) const override;

	/// <summary>
	/// Spawns the object to the specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <returns>
	///		<c>true</c> if successfully spawned; otherwise <c>false</c>.
	/// </returns>
	virtual bool spawn([[maybe_unused]] Player const & player_) override;

	/// <summary>
	/// Despawns the object of the specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	virtual void despawn([[maybe_unused]] Player const & player_) override;

	/// <summary>
	/// Returns the object location for specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <returns>
	/// The object location for specified player.
	/// </returns>
	virtual math::Vector3f getLocationFor([[maybe_unused]] Player const & player_) const override;

	/// <summary>
	/// Returns the object rotation for specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <returns>
	/// The object rotation for specified player.
	/// </returns>
	virtual math::Vector3f getRotationFor([[maybe_unused]] Player const & player_) const override;

	Player const&	m_player;
	Int32			m_handle;
};

}