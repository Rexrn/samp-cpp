#pragma once

#include ADVANCEDGDK_PCH

#include <AdvancedGDK/World/Streamer/Chunk.hpp>
#include <AdvancedGDK/World/Streamer/StreamerSettings.hpp>
#include <AdvancedGDK/Core/Container/DivisibleGrid3.hpp>


namespace agdk::default_streamer
{
class Streamer
{
public:
	// Half extent of the highest-level chunk: 1'638'400;
	// Number of divisions in each iteration: 4
	// Number of iterations: 7
	// Lowest level half extent: 100x100x100
	using GridType = DivisibleGrid3Node<Chunk, std::ratio<1'638'400>, 4, 7>;
 	
	/// <summary>
	/// Event reaction designed to be called when the player changes location significantly.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	void whenPlayerChangesLocation(Player const& player_, PlayerPlacement const& previousPlacement_, PlayerPlacement const& currentPlacement_);

	/// <summary>
	/// Collects every chunk in specified radius from the specified location.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <param name="radius_">The radius.</param>
	/// <returns>Vector of pointers to every collected chunk.</returns>
	std::vector< Chunk* > getChunksInRadiusFrom(math::Vector3f const& location_, math::Meters const radius_);

private:
	GridType m_worldGrid;
};

}
