#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/World/Streamer/Streamer.hpp>

// Object types:
#include <SAMP-EDGEngine/World/GlobalObject.hpp>
#include <SAMP-EDGEngine/World/PersonalObject.hpp>
#include <SAMP-EDGEngine/World/UniversalObject.hpp>

// Wrappers types:
#include <SAMP-EDGEngine/World/Streamer/GlobalObjectWrapper.hpp>
#include <SAMP-EDGEngine/Core/TypesAndDefinitions.hpp>
#include <SAMP-EDGEngine/Server/Server.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>
#include <SAMP-EDGEngine/World/Streamer/PersonalObjectWrapper.hpp>
#include <SAMP-EDGEngine/World/Streamer/UniversalObjectWrapper.hpp>
#include <SAMP-EDGEngine/World/Streamer/CheckpointWrapper.hpp>
#include <SAMP-EDGEngine/World/Streamer/RaceCheckpointWrapper.hpp>

#include <SAMP-EDGEngine/Server/ServerDebugLog.hpp>

namespace samp_edgengine::default_streamer
{

//////////////////////////////////////////////////////////////////////////////////////////////////////
Streamer::Streamer()
	: m_worldGrid{ {} }
{
	Server->onServerUpdate += { *this, &Streamer::update };
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenPlayerJoinsServer(Player & player_)
{
	auto& chunk = this->selectChunk(player_.getLocation());
	chunk.intercept(std::make_unique<PlayerWrapper>(player_));
	
	auto& wrapper = this->getWrapper(player_);
	const_a placement = wrapper.getLastPlacement();
	auto affectedChunks = this->getChunksInRadiusFrom(placement.location, StreamerSettings.VisibilityDistance);

	for (auto chunk : affectedChunks)
		chunk->addScoreAroundPlayer(placement);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenVehicleJoinsMap(Vehicle& vehicle_)
{
	auto& chunk = this->selectChunk(vehicle_.getLocation());
	chunk.intercept( std::make_unique<VehicleWrapper>(vehicle_) );
	this->whenVehiclePlacementChanges(vehicle_, vehicle_.getPlacement(), vehicle_.getPlacement());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenStaticVehicleJoinsMap(StaticVehicle& staticVehicle_)
{
	// Note: this might change in the future.
	this->whenVehicleJoinsMap(staticVehicle_);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenObjectJoinsMap(GlobalObject& globalObject_)
{
	auto& chunk = this->selectChunk(globalObject_.getLocation());
	chunk.intercept( std::make_unique<GlobalObjectWrapper>(globalObject_) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenObjectJoinsMap(PersonalObject& personalObject_)
{
	auto& chunk = this->selectChunk(personalObject_.getLocation());
	chunk.intercept( std::make_unique<PersonalObjectWrapper>(personalObject_) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenObjectJoinsMap(UniversalObject& universalObject_)
{
	auto& chunk = this->selectChunk(universalObject_.getLocation());
	chunk.intercept( std::make_unique<UniversalObjectWrapper>(universalObject_) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenCheckpointJoinsMap(Checkpoint& checkpoint_)
{
	auto& chunk = this->selectChunk(checkpoint_.getLocation());
	chunk.intercept(std::make_unique<CheckpointWrapper>(checkpoint_));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenCheckpointJoinsMap(RaceCheckpoint& raceCheckpoint_)
{
	auto& chunk = this->selectChunk(raceCheckpoint_.getLocation());
	chunk.intercept(std::make_unique<RaceCheckpointWrapper>(raceCheckpoint_));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenPlayerLeavesServer(Player & player_)
{
	auto& wrapper = getWrapper(player_);
	const_a placement = wrapper.getLastPlacement();

	auto affectedChunks = this->getChunksInRadiusFrom(placement.location, StreamerSettings.VisibilityDistance);

	for (auto chunk : affectedChunks)
		chunk->subtractScoreAroundPlayer(placement);


	// Remove spawned objects:
	for (auto spawnedObject : wrapper.spawnedObjects)
	{
		spawnedObject->despawn(player_);
	}

	if (const_a chunk = wrapper.getChunk())
	{
		// Release the stored wrapper.
		auto unused = chunk->release( player_ );
		// Wrapper gets destroyed here, `wrapper` is now invalid reference.
	}

	// Remove the chunk if unused:
	// Note: it is crucial to avoid wasting performance and memory.
	this->checkIfUnusedAndRemove(player_.getLocation());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenVehicleLeavesMap(Vehicle& vehicle_)
{
	auto& wrapper = getWrapper(vehicle_);
	if (const_a chunk = wrapper.getChunk())
	{
		// Release the stored wrapper.
		auto unused = chunk->release( vehicle_ );
		// Wrapper gets destroyed here, `wrapper` is now invalid reference.
	}

	// Remove the chunk if unused:
	// Note: it is crucial to avoid wasting performance and memory.
	this->checkIfUnusedAndRemove(vehicle_.getLocation());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenStaticVehicleLeavesMap(StaticVehicle& staticVehicle_)
{
	// Note: this might change in the future.
	this->whenVehicleLeavesMap(staticVehicle_);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenObjectLeavesMap(GlobalObject& globalObject_)
{
	auto& wrapper = getWrapper(globalObject_);
	if (const_a chunk = wrapper.getChunk())
	{
		// Release the stored wrapper.
		auto unused = chunk->release( globalObject_ );
		// Wrapper gets destroyed here, `wrapper` is now invalid reference.
	}

	// Remove the chunk if unused:
	// Note: it is crucial to avoid wasting performance and memory.
	this->checkIfUnusedAndRemove(globalObject_.getLocation());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenObjectLeavesMap(PersonalObject& personalObject_)
{
	auto& wrapper = getWrapper(personalObject_);
	if (const_a chunk = wrapper.getChunk())
	{
		// Release the stored wrapper.
		auto unused = chunk->release( personalObject_ );
		// Wrapper gets destroyed here, `wrapper` is now invalid reference.
	}

	// Remove the chunk if unused:
	// Note: it is crucial to avoid wasting performance and memory.
	this->checkIfUnusedAndRemove(personalObject_.getLocation());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenObjectLeavesMap(UniversalObject& universalObject_)
{
	auto& wrapper = getWrapper(universalObject_);

	if (const_a chunk = wrapper.getChunk())
	{
		// Release the stored wrapper.
		auto unused = chunk->release(universalObject_);
		// Wrapper gets destroyed here, `wrapper` is now invalid reference.
	}

	// Remove the chunk if unused:
	// Note: it is crucial to avoid wasting performance and memory.
	this->checkIfUnusedAndRemove(universalObject_.getLocation());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenCheckpointLeavesMap(Checkpoint& checkpoint_)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenRaceCheckpointLeavesMap(RaceCheckpoint& raceCheckpoint_)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenPlayerPlacementChanges(Player & player_, PlayerPlacement const& previousPlacement_, PlayerPlacement const& currentPlacement_)
{
	auto affectedChunksPrev = this->getChunksInRadiusFrom(previousPlacement_.location, StreamerSettings.VisibilityDistance);
	auto affectedChunksCurr = this->getChunksInRadiusFrom(currentPlacement_.location, StreamerSettings.VisibilityDistance);

	// Note: make sure that score is added at first and then subtracted, not to cause reference counting error.
	for (auto chunk : affectedChunksCurr)
		chunk->addScoreAroundPlayer(currentPlacement_);

	std::vector<IGlobalActorWrapper*> invalidScoreWrappers;
	invalidScoreWrappers.reserve(1 * 1024);

	for (auto chunk : affectedChunksPrev)
		chunk->subtractScoreAroundPlayer(previousPlacement_, &invalidScoreWrappers);

	invalidScoreWrappers.shrink_to_fit();
	for(auto *invWrapper : invalidScoreWrappers)
		this->recalculateVisibility(*invWrapper, invWrapper->getLocation());

	// EDGE_LOG_DEBUG(Info, "Player {0} has moved, updated {1} invalid objects.", player_.getName(), invalidScoreWrappers.size());

	// Finally apply visibility.
	for (auto chunkList : { &affectedChunksPrev, &affectedChunksCurr })
	{
		for (auto chunk : *chunkList)
			chunk->applyGlobalActorsVisibility();
	}

	// Check whether we should relocate player to new chunk.
	auto& prevChunk = this->selectChunk(previousPlacement_.location);
	auto& currChunk = this->selectChunk(currentPlacement_.location);
	if (&prevChunk != &currChunk)
	{
		currChunk.intercept( prevChunk.release(player_) );
		// Remove the chunk if unused:
		// Note: it is crucial to avoid wasting performance and memory.
		this->checkIfUnusedAndRemove( previousPlacement_.location );
	}

	// Recalculate per-player object visibility
	{
		std::size_t numUniversalInChunks = 0;
		std::size_t numPersonalInChunks = 0;
		for(auto chunk : affectedChunksCurr)
		{
			numUniversalInChunks += chunk->getUniversalObjects().size();
			for(auto const & personal : chunk->getPersonalObjects())
			{
				if (&personal->getObject()->getPlayer() == &player_)
					numPersonalInChunks++;
			}
		}

		std::vector<PerPlayerObject*> objectsInChunks;
		objectsInChunks.reserve(numUniversalInChunks + numPersonalInChunks);

		for(auto chunk : affectedChunksCurr)
		{
			for (auto const & universal : chunk->getUniversalObjects()) {
				objectsInChunks.push_back(universal->getObject());
			}
			for (auto const & personal : chunk->getPersonalObjects())
			{
				if (&personal->getObject()->getPlayer() == &player_)
					objectsInChunks.push_back(personal->getObject());
			}
		}

		// Erase every object outside visibility range:
		objectsInChunks.erase( std::remove_if(objectsInChunks.begin(), objectsInChunks.end(),
			[&player_](PerPlayerObject* object_)
			{
				return !object_->shouldBeVisibleIn(player_.getWorld(), player_.getInterior()) ||
						object_->getLocation().distanceSquared(player_.getLocation()) >= StreamerSettings.getVisibilityDistanceSquared().value;
			}),
			objectsInChunks.end());
		objectsInChunks.shrink_to_fit();

		std::sort(objectsInChunks.begin(), objectsInChunks.end(),
			[&player_](PerPlayerObject* lhs_, PerPlayerObject* rhs_)
			{
				return lhs_->getDistanceSquaredTo(player_) < rhs_->getDistanceSquaredTo(player_);
			});

		if(objectsInChunks.size() > MAX_OBJECTS)
			objectsInChunks.resize(MAX_OBJECTS);

		std::sort(objectsInChunks.begin(), objectsInChunks.end());

		std::vector<PerPlayerObject*> toDespawn(MAX_OBJECTS * 2);

		auto& playerWrapper = getWrapper(player_);

		auto const it = std::set_difference(
			playerWrapper.spawnedObjects.begin(), playerWrapper.spawnedObjects.end(),
			objectsInChunks.begin(), objectsInChunks.end(),
			toDespawn.begin());
		toDespawn.resize(it - toDespawn.begin());

		for (auto object : toDespawn) {
			object->despawn(player_);
		}

		for (auto object : objectsInChunks) {
			object->spawn(player_);
		}

		playerWrapper.spawnedObjects = std::move(objectsInChunks);
	}

	// Recalculate checkpoints
	{
		if (player_.hasStreamedCheckpoints())
			this->streamNearestCheckpointForPlayer(player_);
		if (player_.hasStreamedRaceCheckpoints())
			this->streamNearestRaceCheckpointForPlayer(player_);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenVehiclePlacementChanges(Vehicle & vehicle_, ActorPlacement const& previousPlacement_, ActorPlacement const& currentPlacement_)
{
	auto& wrapper = getWrapper(vehicle_);
	this->recalculateVisibility(wrapper, currentPlacement_.location);

	// Check whether we should relocate vehicle to new chunk.
	auto& prevChunk = this->selectChunk(previousPlacement_.location);
	auto& currChunk = this->selectChunk(currentPlacement_.location);
	if (&prevChunk != &currChunk)
	{
		currChunk.intercept(prevChunk.release(vehicle_));
		// Remove the chunk if unused:
		// Note: it is crucial to avoid wasting performance and memory.
		this->checkIfUnusedAndRemove(previousPlacement_.location);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenStaticVehiclePlacementChanges(StaticVehicle & staticVehicle_, ActorPlacement const& previousPlacement_, ActorPlacement const& currentPlacement_)
{
	// Note: this might change in the future.
	this->whenVehiclePlacementChanges(staticVehicle_, previousPlacement_, currentPlacement_);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenObjectPlacementChanges(GlobalObject & globalObject_, GlobalObjectPlacement const& previousPlacement_, GlobalObjectPlacement const& currentPlacement_)
{
	auto& wrapper = getWrapper(globalObject_);
	this->recalculateVisibility(wrapper, currentPlacement_.location);

	// Check whether we should relocate object to new chunk.
	auto& prevChunk = this->selectChunk(previousPlacement_.location);
	auto& currChunk = this->selectChunk(currentPlacement_.location);
	if (&prevChunk != &currChunk)
	{
		currChunk.intercept(prevChunk.release(globalObject_));
		// Remove the chunk if unused:
		// Note: it is crucial to avoid wasting performance and memory.
		this->checkIfUnusedAndRemove(previousPlacement_.location);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenObjectPlacementChanges(UniversalObject & universalObject_, ActorPlacement const& previousPlacement_, ActorPlacement const& currentPlacement_)
{
	// Check whether we should relocate object to new chunk.
	auto& prevChunk = this->selectChunk(previousPlacement_.location);
	auto& currChunk = this->selectChunk(currentPlacement_.location);
	if (&prevChunk != &currChunk)
	{
		currChunk.intercept(prevChunk.release(universalObject_));
		// Remove the chunk if unused:
		// Note: it is crucial to avoid wasting performance and memory.
		this->checkIfUnusedAndRemove(previousPlacement_.location);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::whenObjectPlacementChanges(PersonalObject & personalObject_, ActorPlacement const& previousPlacement_, ActorPlacement const& currentPlacement_)
{
	// Check whether we should relocate object to new chunk.
	auto& prevChunk = this->selectChunk(previousPlacement_.location);
	auto& currChunk = this->selectChunk(currentPlacement_.location);
	if (&prevChunk != &currChunk)
	{
		currChunk.intercept(prevChunk.release(personalObject_));
		// Remove the chunk if unused:
		// Note: it is crucial to avoid wasting performance and memory.
		this->checkIfUnusedAndRemove(previousPlacement_.location);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector< Chunk* > Streamer::getChunksInRadiusFrom(math::Vector3f const& location_, math::Meters const radius_)
{
	// TODO: create const qualified version of this function.
	// Current method does not collect only chunks from specified radius but from a cube with such half extent.

	constexpr math::Meters	cxNodeHalfExtent	= GridType::ZeroLevelRatio::num / static_cast< double >(GridType::ZeroLevelRatio::den);
	constexpr float			cxNodeHalfExtentF	= static_cast<float>(cxNodeHalfExtent.value);
	auto const				numChunks			= std::size_t( std::ceil((radius_ * 2.0 / cxNodeHalfExtent.value).value) + 4 );

	std::vector< Chunk* > chunks;
	chunks.reserve(numChunks * numChunks * numChunks + 1); // + 1 because we might need to add m_entireWorld

	
	math::Vector3f centerChunkLoc = {
		std::floor((location_.x + cxNodeHalfExtentF) / (cxNodeHalfExtentF * 2)),
		std::floor((location_.y + cxNodeHalfExtentF) / (cxNodeHalfExtentF * 2)),
		std::floor((location_.z + cxNodeHalfExtentF) / (cxNodeHalfExtentF * 2)),
	};
	centerChunkLoc *= static_cast< float >(cxNodeHalfExtent.value * 2);

	const_a hop			= static_cast< float >(cxNodeHalfExtent.value) * 2.f;
	const_a startPoint	= centerChunkLoc - static_cast< float >((numChunks / 2) * hop);
	const_a endPoint	= startPoint + static_cast< float >(numChunks * hop);
	for (float x = startPoint.x; x <= endPoint.x; x += hop)
	{
		for (float y = startPoint.y; y <= endPoint.y; y += hop)
		{
			for (float z = startPoint.z; z <= endPoint.z; z += hop)
			{
				if (Chunk* chunk = m_worldGrid.get({ x, y, z }))
					chunks.push_back(chunk);
			}
		}
	}

	// Calculate whether we should push also the `m_entireWorld` chunk.
	{
		bool shouldPushEntireWorld = false;

		// Note: center is always in { 0, 0, 0 }
		// const_a gridCenter = m_worldGrid.getCenter();
		const_a gridHalfExtent = m_worldGrid.getHalfExtent();
		for(std::size_t i = 0; i < location_.size(); i++)
		{
			if (std::abs(location_[i]) + std::abs(radius_.value) > gridHalfExtent[i])
			{
				shouldPushEntireWorld = true;
				break;
			}
		}
		if (shouldPushEntireWorld)
			chunks.push_back(&m_entireWorld);
	}

	return chunks;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::update(double deltaTime_, IUpdatable::TimePoint frameTime_)
{
	if (frameTime_ > m_nextUpdate)
	{
		m_nextUpdate = frameTime_ + StreamerSettings.UpdateInterval;

		bool shouldRestreamCheckpoints = false;
		if (m_nextCheckpointRestream < frameTime_)
		{
			shouldRestreamCheckpoints = true;
			m_nextCheckpointRestream = frameTime_ + StreamerSettings.CheckpointRestreamInterval;
		}

		for(auto player : GameMode->players.getPool())
		{
			if (player) {

				player->sendPlacementUpdate();

				if (shouldRestreamCheckpoints)
				{
					if (player->hasStreamedCheckpoints())
						this->streamNearestCheckpointForPlayer(*player);

					if (player->hasStreamedRaceCheckpoints())
						this->streamNearestRaceCheckpointForPlayer(*player);
				}
			}
		}

		for(auto vehicle : GameMode->map.getVehicles()) {
			vehicle->sendPlacementUpdate();
		}
		for (auto vehicle : GameMode->map.getStaticVehicles()) {
			vehicle->sendPlacementUpdate();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::recalculateVisibility(IGlobalActorWrapper &wrapper_, math::Vector3f location_)
{
	auto chunksAround = this->getChunksInRadiusFrom(location_, StreamerSettings.VisibilityDistance);

	Int16 visibilityIndex = 0;
	for (auto chunk : chunksAround)
	{
		for (const_a& playerWrapper : chunk->getPlayers())
		{
			if (wrapper_.isPlayerInVisibilityZone(playerWrapper->getLastPlacement()))
			{
				visibilityIndex++;
			}
		}
	}
	wrapper_.setVisibilityIndex(visibilityIndex);
	wrapper_.applyVisibility();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
bool Streamer::isOutsideGridBoundaries(math::Vector3f const& location_) const
{
	return !m_worldGrid.containsPoint(location_);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
Chunk& Streamer::selectChunk(math::Vector3f const& location_)
{
	return this->isOutsideGridBoundaries(location_) ? m_entireWorld : m_worldGrid.require(location_);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::checkIfUnusedAndRemove(math::Vector3f const& location_)
{
	if (!this->isOutsideGridBoundaries(location_))
	{
		if ( auto const chunk = m_worldGrid.get(location_) )
		{
			if (chunk->isEmpty()) {
				m_worldGrid.removeNode(location_);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::streamNearestCheckpointForPlayer(Player& player_)
{
	auto chunksInRadius = this->getChunksInRadiusFrom(player_.getLocation(), StreamerSettings.VisibilityDistance);

	std::vector<Checkpoint*> checkpoints;

	std::size_t numCheckpoints = 0;
	for(auto chunk : chunksInRadius)
	{
		numCheckpoints += chunk->getCheckpoints().size();
	}

	checkpoints.reserve(numCheckpoints);

	for (auto chunk : chunksInRadius)
	{
		for (auto const& checkpointWrapper : chunk->getCheckpoints())
		{
			auto checkpoint = checkpointWrapper->getCheckpoint();

			// Sort out checkpoints that are either too far or in wrong world/interior.
			if (checkpoint->shouldBeVisibleIn(player_.getWorld(), player_.getInterior()) &&
				checkpoint->getLocation().distanceSquared(player_.getLocation()) <= StreamerSettings.getVisibilityDistanceSquared().value)
			{
				checkpoints.push_back(checkpoint);
			}
		}
	}

	auto nearestCheckpointIt = std::min_element(checkpoints.begin(), checkpoints.end(),
		[&player_](Checkpoint* left_, Checkpoint* right_)
		{
			return left_->getLocation().distanceSquared(player_.getLocation()) < right_->getLocation().distanceSquared(player_.getLocation());
		});

	if (nearestCheckpointIt != checkpoints.end())
	{
		if (*(*nearestCheckpointIt) != player_.getLastCheckpoint())
			player_.setCheckpoint(*(*nearestCheckpointIt));
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void Streamer::streamNearestRaceCheckpointForPlayer(Player& player_)
{
	auto chunksInRadius = this->getChunksInRadiusFrom(player_.getLocation(), StreamerSettings.VisibilityDistance);

	std::vector<RaceCheckpoint*> checkpoints;

	std::size_t numCheckpoints = 0;
	for(auto chunk : chunksInRadius)
	{
		numCheckpoints += chunk->getRaceCheckpoints().size();
	}

	checkpoints.reserve(numCheckpoints);

	for (auto chunk : chunksInRadius)
	{
		for (auto const& checkpointWrapper : chunk->getRaceCheckpoints())
		{
			auto checkpoint = checkpointWrapper->getCheckpoint();

			// Sort out checkpoints that are either too far or in wrong world/interior.
			if (checkpoint->shouldBeVisibleIn(player_.getWorld(), player_.getInterior()) &&
				checkpoint->getLocation().distanceSquared(player_.getLocation()) <= StreamerSettings.getVisibilityDistanceSquared().value)
			{
				checkpoints.push_back(static_cast<RaceCheckpoint*>(checkpoint));
			}
		}
	}

	auto nearestCheckpointIt = std::min_element(checkpoints.begin(), checkpoints.end(),
		[&player_](RaceCheckpoint* left_, RaceCheckpoint* right_)
		{
			return left_->getLocation().distanceSquared(player_.getLocation()) < right_->getLocation().distanceSquared(player_.getLocation());
		});

	if (nearestCheckpointIt != checkpoints.end())
	{
		if (*(*nearestCheckpointIt) != player_.getLastRaceCheckpoint())
			player_.setRaceCheckpoint(*(*nearestCheckpointIt));
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
PlayerWrapper& Streamer::getWrapper(Player const& player_)
{
	// Note: static cast used to improve performance. It is guaranteed (until mistakenly coded) that this cast is valid if tracker is set.
	if(const_a wrapper = static_cast<PlayerWrapper*>(player_.getPlacementTracker()))
	{
		return *wrapper;
	} else
		throw std::invalid_argument("The specified player does not have placement tracker set.");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
VehicleWrapper& Streamer::getWrapper(Vehicle const& vehicle_)
{
	// Note: static cast used to improve performance. It is guaranteed (until mistakenly coded) that this cast is valid if tracker is set.
	if(const_a wrapper = static_cast<VehicleWrapper*>(vehicle_.getPlacementTracker()))
	{
		return *wrapper;
	} else
		throw std::invalid_argument("The specified vehicle does not have placement tracker set.");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
GlobalObjectWrapper& Streamer::getWrapper(GlobalObject const& globalObject_)
{
	// Note: static cast used to improve performance. It is guaranteed (until mistakenly coded) that this cast is valid if tracker is set.
	if(const_a wrapper = static_cast<GlobalObjectWrapper*>(globalObject_.getPlacementTracker()))
	{
		return *wrapper;
	} else
		throw std::invalid_argument("The specified global object does not have placement tracker set.");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
PersonalObjectWrapper& Streamer::getWrapper(PersonalObject const& personalObject_)
{
	// Note: static cast used to improve performance. It is guaranteed (until mistakenly coded) that this cast is valid if tracker is set.
	if (const_a wrapper = static_cast<PersonalObjectWrapper*>(personalObject_.getPlacementTracker()))
	{
		return *wrapper;
	}
	else
		throw std::invalid_argument("The specified personal object does not have placement tracker set.");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
UniversalObjectWrapper& Streamer::getWrapper(UniversalObject const& universalObject_)
{
	// Note: static cast used to improve performance. It is guaranteed (until mistakenly coded) that this cast is valid if tracker is set.
	if (const_a wrapper = static_cast<UniversalObjectWrapper* > (universalObject_.getPlacementTracker()))
	{
		return *wrapper;
	}
	else
		throw std::invalid_argument("The specified universal object does not have placement tracker set.");
}

} // namespace agdk::default_streamer
