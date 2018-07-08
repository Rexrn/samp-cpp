#pragma once

#include SAMP_EDGENGINE_EXT_RESOURCEIO_PCH

#include <SAMP-EDGEngine-Ext/ResourceIO/Deserializer.hpp>

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// An interface to every <see cref="RemovedBuilding"/> deserialization algorithm.
/// </summary>
struct IRemovedBuildingDeserializer
	: virtual IDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="IRemovedBuildingDeserializer"/> struct.
	/// </summary>
	/// <param name="removedBuilding_">The removed building.</param>
	IRemovedBuildingDeserializer(RemovedBuilding & removedBuilding_)
		: removedBuilding{ removedBuilding_ }
	{
	}

	// The deserialized scene:
	RemovedBuilding & removedBuilding;
};

}