#pragma once

#include ADVANCEDGDK_PCH

#include <AdvancedGDK/Core/MathInc.hpp>

namespace agdk::default_streamer
{

/// <summary>
/// Contains streamer settings
/// </summary>
struct StreamerSettingsType
{
	// Precalculated values:
	math::Meters VisibilityDistance			= 300.0;			// From what distance object should pop into view?
	math::Meters MaxDisplacementDistance	= 30.0;				// When displacement reaches this value the change is a significant one.


	// Methods:	

	/// <summary>
	/// Initializes a new instance of the <see cref="StreamerSettingsType"/> struct.
	/// </summary>
	StreamerSettingsType() {
		this->precalculate();
	}
	
	/// <summary>
	/// Precalculates additional values, that depend on the public ones.
	/// </summary>
	void precalculate()
	{
		// Precalculate every additional value:
		m_visibilityDistanceSq			= VisibilityDistance * VisibilityDistance.value;
		m_maxDisplacementDistanceSq		= MaxDisplacementDistance * MaxDisplacementDistance.value;
	}

	// Getters:
	auto getVisibilityDistanceSquared() const {
		return m_visibilityDistanceSq;
	}

	auto getMaxDisplacementDistanceSquared() const {
		return m_maxDisplacementDistanceSq;
	}

private:
	math::Meters m_visibilityDistanceSq;
	math::Meters m_maxDisplacementDistanceSq;

} inline StreamerSettings;

}
