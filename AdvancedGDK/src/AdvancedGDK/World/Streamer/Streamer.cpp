#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/Streamer/Streamer.hpp>

namespace agdk::default_streamer
{

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenPlayerChangesLocation(Player const& player_, PlayerPlacement const& previousPlacement_, PlayerPlacement const& currentPlacement_)
{
	auto affectedChunksPrev = this->getChunksInRadiusFrom(previousPlacement_.location, StreamerSettings.VisibilityDistance);
	auto affectedChunksCurr = this->
		getChunksInRadiusFrom(currentPlacement_.location, StreamerSettings.VisibilityDistance);

	// Note: make sure that score is added at first and then subtracted, not to cause reference counting error.
	for (auto chunk : affectedChunksCurr)
		chunk->addScoreAroundPlayer(currentPlacement_);

	for (auto chunk : affectedChunksPrev)
		chunk->subtractScoreAroundPlayer(previousPlacement_);

	// Finally apply visibility.
	for (auto chunkList : { &affectedChunksPrev, &affectedChunksCurr })
	{
		for (auto chunk : *chunkList)
			chunk->applyGlobalActorsVisibility();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector< Chunk* > Streamer::getChunksInRadiusFrom(math::Vector3f const& location_, math::Meters const radius_)
{
	// TODO: create const qualified version of this function.
	// Current method does not collect only chunks from specified radius but from a cube with such half extent.

	constexpr math::Meters nodeHalfExtent = GridType::ZeroLevelRatio::num / static_cast< double >(GridType::ZeroLevelRatio::den);
	std::size_t numChunks = math::ceil((radius_ * 2.0 / nodeHalfExtent.value).value) + 2;

	std::vector< Chunk* > chunks;
	chunks.reserve(numChunks * numChunks * numChunks);

	math::Vector3f centerChunkLoc = {
		std::floor((location_.x + nodeHalfExtent.value) / (nodeHalfExtent.value * 2)),
		std::floor((location_.y + nodeHalfExtent.value) / (nodeHalfExtent.value * 2)),
		std::floor((location_.z + nodeHalfExtent.value) / (nodeHalfExtent.value * 2)),
	};
	centerChunkLoc *= static_cast< float >(nodeHalfExtent.value * 2);

	float hop = static_cast< float >(nodeHalfExtent.value) * 2.f;
	math::Vector3f startPoint = centerChunkLoc - static_cast< float >((numChunks / 2) * hop);
	math::Vector3f endPoint = startPoint + static_cast< float >(numChunks * hop);
	for (float x = startPoint.x; x <= endPoint.x; x += hop)
	{
		for (float y = startPoint.y; y <= endPoint.y; y += hop)
		{
			for (float z = startPoint.z; z <= endPoint.z; z += hop)
			{
				Chunk* chunk = m_worldGrid.get({ x, y, z });
				chunks.push_back(chunk);
			}
		}
	}
	return chunks;
}
}
