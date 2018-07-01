#pragma once

// Base class:
#include <SAMP-EDGEngine/World/Streamer/GlobalActorWrapper.hpp>
#include <SAMP-EDGEngine/Core/BasicInterfaces/PlacementTracker.hpp>

// Wrapped class:
#include <SAMP-EDGEngine/World/GlobalObject.hpp>

namespace agdk
{

namespace default_streamer
{
	
class GlobalObjectWrapper
	:
	public IGlobalActorWrapper,
	public IGlobalObjectPlacementTracker
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="GlobalObjectWrapper"/> class.
	/// </summary>
	/// <param name="object_">The object.</param>
	GlobalObjectWrapper(GlobalObject & object_);

	/// <summary>
	/// Sets the underlying object.
	/// </summary>
	/// <param name="object_">The object.</param>
	void setObject(GlobalObject& object_);

	/// <summary>
	/// Returns the underlying object.
	/// </summary>
	/// <returns>The underlying object.</returns>
	GlobalObject* getObject() const {
		return m_object;
	}

	// Overriden methods from IGlobalActorWrapper:

	/// <summary>
	/// Changes vehicle visibility which depends on its visibility index.
	/// </summary>
	virtual void applyVisibility() override;

	/// <summary>
	/// Determines whether the specified player is in the visibility zone.
	/// </summary>
	/// <param name="placement_">The player's placement.</param>
	/// <returns>
	///		<c>true</c> if is in visibility zone; otherwise, <c>false</c>.
	/// </returns>
	virtual bool isPlayerInVisibilityZone(PlayerPlacement const& placement_) const override;
	
	/// <summary>
	/// Event reaction called when placement changes significantly.
	/// </summary>
	/// <param name="prevPlacement_">The previous placement.</param>
	/// <param name="newPlacement_">The new placement.</param>
	virtual void whenPlacementChanges(GlobalObjectPlacement const& prevPlacement_, GlobalObjectPlacement const& newPlacement_) override;

private:

	GlobalObject * m_object; // The underlying object.
};

} // namespace default_streamer

} // namespace agdk
