#pragma once

#include <AdvancedGDK/World/Actor.hpp>

namespace agdk::default_streamer
{
class Chunk;

/// <summary>
/// Base class for every actor inside a chunk - wraps around a world actor.
/// </summary>
class IChunkActor
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="IStreamable"/> class.
	/// </summary>
	explicit IChunkActor();

	/// <summary>
	/// Finalizes an instance of the <see cref="IChunkActor"/> class.
	/// </summary>
	virtual ~IChunkActor() = default;

	/// <summary>
	/// Sets chunk the object belongs to.
	/// </summary>
	/// <param name="chunk_">The chunk.</param>
	void setChunk(Chunk& chunk_);

	/// <summary>
	/// Returns the chunk instance belongs to.
	/// </summary>
	/// <returns>The chunk instance belongs to. May be nullptr.</returns>
	Chunk* getChunk() const;

protected:

	Chunk* m_chunk; // Chunk in which actor is located.
};

}
