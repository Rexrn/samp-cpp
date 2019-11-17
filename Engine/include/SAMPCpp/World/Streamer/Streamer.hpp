#pragma once
#include SAMPCPP_PCH



#include <SAMPCpp/World/Streamer/Chunk.hpp>
#include <SAMPCpp/World/Streamer/StreamerSettings.hpp>
#include <SAMPCpp/Core/Container/DivisibleGrid3.hpp>
#include <SAMPCpp/Core/BasicInterfaces/Streamer.hpp>
#include <SAMPCpp/Core/BasicInterfaces/Updatable.hpp>
#include <SAMPCpp/Core/Events.hpp>


namespace samp_cpp::default_streamer
{
class Streamer
	:
	public IStreamer,
	public IEventReceiver,
	public IUpdatable
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Streamer"/> class.
	/// </summary>
	Streamer();

	// Half extent of the highest-level chunk: 1'638'400;
	// Number of divisions in each iteration: 4
	// Number of iterations: 7
	// Lowest level half extent: 100x100x100
	using GridType = DivisibleGrid3Node<Chunk, std::ratio<1'638'400>, 4, 7>;
 		
	/// <summary>
	/// Event reaction designed to be called when player joins the server.
	/// </summary>
	/// <param name="player_">The player.</param>
	virtual void whenPlayerJoinsServer(Player & player_) override;
	
	/// <summary>
	/// Event reaction designed to be called when vehicle joins map.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	virtual void whenVehicleJoinsMap(Vehicle& vehicle_) override;
	
	/// <summary>
	/// Event reaction designed to be called when static vehicle joins map.
	/// </summary>
	/// <param name="staticVehicle_">The static vehicle.</param>
	void whenStaticVehicleJoinsMap(StaticVehicle& staticVehicle_) override;
	
	/// <summary>
	/// Event reaction designed to be called when global object joins map.
	/// </summary>
	/// <param name="globalObject_">The global object.</param>
	virtual void whenObjectJoinsMap(GlobalObject& globalObject_) override;
	
	/// <summary>
	/// Event reaction designed to be called when personal object joins map.
	/// </summary>
	/// <param name="personalObject_">The personal object.</param>
	virtual void whenObjectJoinsMap(PersonalObject& personalObject_) override;
	
	/// <summary>
	/// Event reaction designed to be called when universal object joins map.
	/// </summary>
	/// <param name="universalObject_">The universal object.</param>
	virtual void whenObjectJoinsMap(UniversalObject& universalObject_) override;
	
	/// <summary>
	/// Event reaction designed to be called when checkpoint joins map.
	/// </summary>
	/// <param name="checkpoint_">The checkpoint.</param>
	virtual void whenCheckpointJoinsMap(Checkpoint& checkpoint_) override;
	
	/// <summary>
	/// Event reaction designed to be called when race checkpoint joins map.
	/// </summary>
	/// <param name="raceCheckpoint_">The race checkpoint.</param>
	virtual void whenCheckpointJoinsMap(RaceCheckpoint& raceCheckpoint_) override;

	/// <summary>
	/// Event reaction designed to be called when player leaves the server.
	/// </summary>
	/// <param name="player_">The player.</param>
	virtual void whenPlayerLeavesServer(Player & player_) override;
	
	/// <summary>
	/// Event reaction designed to be called when vehicle leaves map.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	virtual void whenVehicleLeavesMap(Vehicle& vehicle_) override;
	
	/// <summary>
	/// Event reaction designed to be called when static vehicle leaves map.
	/// </summary>
	/// <param name="staticVehicle_">The static vehicle.</param>
	void whenStaticVehicleLeavesMap(StaticVehicle& staticVehicle_) override;
	
	/// <summary>
	/// Event reaction designed to be called when global object leaves the map.
	/// </summary>
	/// <param name="globalObject_">The global object.</param>
	virtual void whenObjectLeavesMap(GlobalObject& globalObject_) override;
	
	/// <summary>
	/// Event reaction designed to be called when personal object leaves map.
	/// </summary>
	/// <param name="personalObject_">The personal object.</param>
	virtual void whenObjectLeavesMap(PersonalObject& personalObject_) override;
	
	/// <summary>
	/// Event reaction designed to be called when universal object leaves map.
	/// </summary>
	/// <param name="universalObject_">The universal object.</param>
	virtual void whenObjectLeavesMap(UniversalObject& universalObject_) override;
	
	/// <summary>
	/// Event reaction designed to be called when checkpoint leaves map.
	/// </summary>
	/// <param name="checkpoint_">The checkpoint.</param>
	virtual void whenCheckpointLeavesMap(Checkpoint& checkpoint_) override;
	
	/// <summary>
	/// Event reaction designed to be called when race checkpoint leaves map.
	/// </summary>
	/// <param name="raceCheckpoint_">The race checkpoint.</param>
	virtual void whenRaceCheckpointLeavesMap(RaceCheckpoint& raceCheckpoint_) override;

	/// <summary>
	/// Event reaction designed to be called when the player changes location significantly.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	virtual void whenPlayerPlacementChanges(Player & player_, PlayerPlacement const& previousPlacement_, PlayerPlacement const& currentPlacement_) override;
	
	/// <summary>
	/// Event reaction designed to be called when the vehicle changes location significantly.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	virtual void whenVehiclePlacementChanges(Vehicle & vehicle_, ActorPlacement const& previousPlacement_, ActorPlacement const& currentPlacement_) override;
		
	/// <summary>
	/// Event reaction designed to be called when the static vehicle changes location significantly.
	/// </summary>
	/// <param name="staticVehicle_">The static vehicle_.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	void whenStaticVehiclePlacementChanges(StaticVehicle & staticVehicle_, ActorPlacement const& previousPlacement_, ActorPlacement const& currentPlacement_) override;

	/// <summary>
	/// Event reaction designed to be called when the global object changes location significantly.
	/// </summary>
	/// <param name="globalObject_">The global object.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	void whenObjectPlacementChanges(GlobalObject & globalObject_, GlobalObjectPlacement const& previousPlacement_, GlobalObjectPlacement const& currentPlacement_) override;
	
	/// <summary>
	/// Event reaction designed to be called when the universal object changes location significantly.
	/// </summary>
	/// <param name="universalObject_">The universal object.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	void whenObjectPlacementChanges(UniversalObject & universalObject_, ActorPlacement const& previousPlacement_, ActorPlacement const& currentPlacement_) override;
	
	/// <summary>
	/// Event reaction designed to be called when the personal object changes location significantly.
	/// </summary>
	/// <param name="personalObject_">The personal object.</param>
	/// <param name="previousPlacement_">The previous placement.</param>
	/// <param name="currentPlacement_">The current placement.</param>
	void whenObjectPlacementChanges(PersonalObject & personalObject_, ActorPlacement const& previousPlacement_, ActorPlacement const& currentPlacement_) override;


	/// <summary>
	/// Collects every chunk in specified radius from the specified location.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <param name="radius_">The radius.</param>
	/// <returns>Vector of pointers to every collected chunk.</returns>
	std::vector< Chunk* > getChunksInRadiusFrom(math::Vector3f const& location_, math::Meters const radius_);

private:

	/// <summary>
	/// Event reaction designed to be called every update.
	/// </summary>
	/// <param name="frameTime_">The frame time.</param>
	virtual void update(double deltaTime_, IUpdatable::TimePoint frameTime_) override;

	/// <summary>
	/// Recalculates actor visibility.
	/// </summary>
	/// <param name="wrapper_">Actor wrapper to update.</param>
	/// <param name="location_">Custom location of the object, because last placement is not always the case.</param>
	void recalculateVisibility(IGlobalActorWrapper &wrapper_, math::Vector3f location_);

	/// <summary>
	/// Determines whether specified location is outside boundaries.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <returns>
	///   <c>true</c> if location is outside boundaries; otherwise, <c>false</c>.
	/// </returns>
	bool isOutsideGridBoundaries(math::Vector3f const & location_) const;
	
	/// <summary>
	/// Selects the chunk using the location. Returns reference to `m_entireWorld` if location is outside world grid bounds.
	/// </summary>
	/// <param name="location_">The location.</param>
	/// <returns>Reference to chunk containing specified location.</returns>
	Chunk& selectChunk(math::Vector3f const & location_);
		
	/// <summary>
	/// Checks if chunk in specified location is unused and if so - removes it. It won't try to remove `m_entireWorld`.
	/// </summary>
	/// <param name="location_">The location.</param>
	void checkIfUnusedAndRemove(math::Vector3f const & location_);
	
	/// <summary>
	/// Streams the nearest checkpoint for player.
	/// </summary>
	/// <param name="player_">The player.</param>
	void streamNearestCheckpointForPlayer(Player &player_);

	/// <summary>
	/// Streams the nearest race checkpoint for player.
	/// </summary>
	/// <param name="player_">The player.</param>
	void streamNearestRaceCheckpointForPlayer(Player &player_);

	/// <summary>
	/// Returns reference to player wrapper.
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <returns>Reference to player wrapper.</returns>
	/// <remarks>
	///		<para>Throws `std::invalid_argument` of player has no wrapper set.</para>
	/// </remarks>
	static PlayerWrapper& getWrapper(Player const & player_);

	/// <summary>
	/// Returns reference to vehicle wrapper.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	/// <returns>Reference to vehicle wrapper.</returns>
	/// <remarks>
	///		<para>Throws `std::invalid_argument` of vehicle has no wrapper set.</para>
	/// </remarks>
	static VehicleWrapper& getWrapper(Vehicle const & vehicle_);

	/// <summary>
	/// Returns reference to global object wrapper.
	/// </summary>
	/// <param name="globalObject_">The global object.</param>
	/// <returns>Reference to global object wrapper.</returns>
	/// <remarks>
	///		<para>Throws `std::invalid_argument` of global object has no wrapper set.</para>
	/// </remarks>
	static GlobalObjectWrapper& getWrapper(GlobalObject const & globalObject_);

	/// <summary>
	/// Returns reference to personal object wrapper.
	/// </summary>
	/// <param name="personalObject_">The personal object.</param>
	/// <returns>Reference to personal object wrapper.</returns>
	/// <remarks>
	///		<para>Throws `std::invalid_argument` of personal object has no wrapper set.</para>
	/// </remarks>
	static PersonalObjectWrapper& getWrapper(PersonalObject const & personalObject_);

	/// <summary>
	/// Returns reference to universal object wrapper.
	/// </summary>
	/// <param name="universalObject_">The universal object.</param>
	/// <returns>Reference to universal object wrapper.</returns>
	/// <remarks>
	///		<para>Throws `std::invalid_argument` of universal object has no wrapper set.</para>
	/// </remarks>
	static UniversalObjectWrapper& getWrapper(UniversalObject const & universalObject_);

	IUpdatable::TimePoint	m_nextUpdate,
							m_nextCheckpointRestream;

	GridType				m_worldGrid;	// Stores chunks in certain area (typically huge cube with center on {0, 0, 0}) as divisible grid. Searching through it is really fast.
	Chunk					m_entireWorld;	// Contains every actor that does not fit outside m_worldGrid. Searching through this chunks is a lot slower since it is not divided into smaller ones.
};

}