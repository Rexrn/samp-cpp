#pragma once

// Direct base class:
#include <AdvancedGDK/World/Streamer/ChunkActor.hpp>

// Additional includes:
#include <AdvancedGDK/Server/Player/Player.hpp>
#include <AdvancedGDK/Core/Exceptions.hpp>

namespace agdk
{

namespace default_streamer
{

/// <summary>
/// A base class for global objects and vehicles (wrapped in streamer classes).
/// </summary>
class IGlobalActorWrapper
	: public IChunkActor
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="IGlobalActorWrapper"/> class.
	/// </summary>
	explicit IGlobalActorWrapper();

	/// <summary>
	/// Designed to be called when player enters the visibility zone.
	/// </summary>
	void whenPlayerEntersVisibilityZone();

	/// <summary>
	/// Designed to be called when player leaves the visibility zone.
	/// </summary>
	void whenPlayerLeavesVisibilityZone();

	/// <summary>
	/// Returns the visibility index.
	/// </summary>
	/// <returns>Visibility index.</returns>
	std::uint16_t getVisibilityIndex() const;

	/// <summary>
	/// Determines whether the specified player is in the visibility zone.
	/// </summary>
	/// <param name="placement_">The player's placement.</param>
	/// <returns>
	///		<c>true</c> if is in visibility zone; otherwise, <c>false</c>.
	/// </returns>
	/// <remarks>
	///		<para>
	///		Note: this function implementation will differ between global object and vehicle,
	///		since vehicles can be bound to specific world and interior and virtual world.
	///		</para>
	/// </remarks>
	virtual bool isPlayerInVisibilityZone(PlayerPlacement const & placement_) const = 0;
	
	/// <summary>
	/// Changes object visibility which depends on its visibility index.
	/// </summary>
	virtual void applyVisibility() = 0;

	/// <summary>
	/// Returns true if actor should be visible (its visibility index is > 0).
	/// </summary>
	/// <returns>
	///		<c>true</c> if actor should be visible; otherwise, <c>false</c>.
	/// </returns>
	bool shouldBeVisible() const {
		return m_visibilityIndex > 0;
	}
private:

	std::uint16_t m_visibilityIndex; // Number of players currently seeing the object.
};

} // namespace default_streamer

} // namespace agdk
