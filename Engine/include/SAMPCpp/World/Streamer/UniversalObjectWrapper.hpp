#pragma once
#include SAMPCPP_PCH



#include <SAMPCpp/World/UniversalObject.hpp>
#include <SAMPCpp/Core/BasicInterfaces/PlacementTracker.hpp>
#include <SAMPCpp/World/Streamer/ChunkActor.hpp>

namespace samp_cpp
{

namespace default_streamer
{

class UniversalObjectWrapper
	:
	public IChunkActor,
	public I3DNodePlacementTracker
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="UniversalObjectWrapper"/> class.
	/// </summary>
	/// <param name="object_">The object.</param>
	UniversalObjectWrapper(UniversalObject & object_);

	/// <summary>
	/// Sets pointer to the underlying object.
	/// </summary>
	/// <param name="object_">The object.</param>
	void setObject(UniversalObject & object_);

	/// <summary>
	/// Returns pointer to the underlying object.
	/// </summary>
	/// <returns>Pointer to the underlying object.</returns>
	UniversalObject* getObject() const {
		return m_object;
	}

	/// <summary>
	/// Event reaction called when placement changes significantly.
	/// </summary>
	/// <param name="prevPlacement_">The previous placement.</param>
	/// <param name="newPlacement_">The new placement.</param>
	void whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_) override;

private:
	UniversalObject * m_object;
};

}

}
