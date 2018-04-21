#pragma once

#include <AdvancedGDK/World/Actor.hpp>

namespace agdk
{
class Chunk;

/// <summary>
/// Base class for every actor inside a chunk - wraps a world actor.
/// </summary>
template <typename TActorType>
class IChunkActor
{
public:
	using ActorType = TActorType;

	/// <summary>
	/// Initializes a new instance of the <see cref="IStreamable"/> class.
	/// </summary>
	explicit IChunkActor(ActorType &actor_)
		: m_actor{ &actor_ }, m_chunk{ nullptr }
	{	
	}

	/// <summary>
	/// Returns the chunk instance belongs to.
	/// </summary>
	/// <returns>The chunk instance belongs to. May be nullptr.</returns>
	Chunk* getChunk() const {
		return m_chunk;
	}

	/// <summary>
	/// Returns stored actor.
	/// </summary>
	/// <returns>Stored actor.</returns>
	ActorType* getActor() const {
		return m_actor;
	}

	friend class Chunk;
protected:
	/// <summary>
	/// Sets chunk the object belongs to.
	/// </summary>
	/// <param name="chunk_">The chunk.</param>
	void setChunk(Chunk& chunk_) {
		m_chunk = &chunk_;
	}

	ActorType*		m_actor; // Actor represented by this instance.
	Chunk*			m_chunk; // Chunk in which actor is located.
};

}
