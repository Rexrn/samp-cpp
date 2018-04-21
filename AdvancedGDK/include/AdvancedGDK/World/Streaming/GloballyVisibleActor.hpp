#pragma once

#include "ChunkActor.hpp"

#include <AdvancedGDK/Core/Exceptions.hpp>

namespace agdk
{

class GloballyVisibleActor
{
public:
	
	/// <summary>
	/// Initializes a new instance of the <see cref="GloballyStreamable"/> class.
	/// </summary>
	explicit GloballyVisibleActor()
		: m_visibilityIndex{ 0 }
	{
	}
	
	/// <summary>
	/// Designed to be called when player enters the visibility zone.
	/// </summary>
	void playerEnteredVisibilityZone()
	{
		m_visibilityIndex++;
	}
	
	/// <summary>
	/// Designed to be called when player leaves the visibility zone.
	/// </summary>
	void playerLeftVisibilityZone()
	{
		if (m_visibilityIndex > 0)
			m_visibilityIndex--;
		else
			throw ReferenceCountingError("More players exited area than entered - counting mismatch.");
	}
	
	/// <summary>
	/// Returns the visibility index.
	/// </summary>
	/// <returns>Visibility index.</returns>
	std::uint16_t getVisibilityIndex() const {
		return m_visibilityIndex;
	}
private:

	std::uint16_t m_visibilityIndex; // Number of players currently seeing the object.
};

}
