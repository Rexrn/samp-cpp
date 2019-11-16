#pragma once
#include SAMPEDGENGINE_PCH



#include <SAMP-EDGEngine/World/3DNode.hpp>

namespace samp_cpp::default_streamer
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

	friend class Chunk;
protected:

	/// <summary>
	/// Resets chunk pointer to nullptr.
	/// </summary>
	/// <param name="ptr_">The nullptr.</param>
	void setChunk(std::nullptr_t ptr_);

	Chunk* m_chunk; // Chunk in which actor is located.
};

}
