#pragma once

#include SAMP_EDGENGINE_EXT_RESOURCEIO_PCH

#include <SAMP-EDGEngine-Ext/ResourceIO/Serializer.hpp>

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// An interface to every <see cref="RemovedBuilding"/> serialization algorithm.
/// </summary>
struct IRemovedBuildingSerializer
	: virtual ISerializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="IRemovedBuildingSerializer"/> struct.
	/// </summary>
	/// <param name="removedBuilding_">The removed building.</param>
	IRemovedBuildingSerializer(RemovedBuilding const& removedBuilding_)
		: removedBuilding{ removedBuilding_ }
	{
	}

	// The serialized scene:
	RemovedBuilding const& removedBuilding;
};

}