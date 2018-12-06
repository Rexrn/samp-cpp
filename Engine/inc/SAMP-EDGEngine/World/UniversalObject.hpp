#pragma once

// Base class header:
#include <SAMP-EDGEngine/World/PerPlayerObject.hpp>

namespace samp_edgengine
{

/// <summary>
/// Object that is visible for every player, but is streamed, not global.
/// </summary>
/// <seealso cref="PerPlayerObject" />
class UniversalObject
	: public PerPlayerObject
{
public:
	/// <summary>
	/// Finalizes an instance of the <see cref="UniversalObject"/> class.
	/// </summary>
	virtual ~UniversalObject();

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
	virtual bool spawn(Player const & player_) override;
	
	/// <summary>
	/// Despawns the object of the specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	virtual void despawn(Player const & player_) override;
	
	/// <summary>
	/// Returns the object location for specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <returns>
	/// The object location for specified player.
	/// </returns>
	virtual math::Vector3f getLocationFor(Player const & player_) const override;

	/// <summary>
	/// Returns the object rotation for specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <returns>
	/// The object rotation for specified player.
	/// </returns>
	virtual math::Vector3f getRotationFor(Player const & player_) const override;
	
	/// <summary>
	/// Returns object type.
	/// </summary>
	/// <returns>
	///		Type of the object.
	/// </returns>
	virtual Type getType() const override {
		return Type::Universal;
	}
protected:
	/// <summary>
	/// Applies the text.
	/// </summary>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="textMaterial_">The text material.</param>
	/// <param name="player_">The player.</param>
	virtual void applyText(std::size_t const materialIndex_, Text const & textMaterial_, const Player * player_) override;

	/// <summary>
	/// Applies the texture.
	/// </summary>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="textureMaterial_">The texture material.</param>
	/// <param name="player_">The player.</param>
	virtual void applyTexture(std::size_t const materialIndex_, Texture const & textureMaterial_, const Player * player_) override;
	
	using PlayerHandle = std::pair<Player const*, Int32>;
	using HandlesContainer = std::vector < PlayerHandle >;

	/// <summary>
	/// Finds the object handle for player inside the handle container.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <returns>Iterator of the handle container.</returns>
	auto findHandleForPlayer(Player const & player_)
	{
		return std::find_if(m_playerHandles.begin(), m_playerHandles.end(),
			[&player_](PlayerHandle const & pair_)
			{
				return pair_.first == &player_;
			});
	}

	HandlesContainer m_playerHandles;
};


}