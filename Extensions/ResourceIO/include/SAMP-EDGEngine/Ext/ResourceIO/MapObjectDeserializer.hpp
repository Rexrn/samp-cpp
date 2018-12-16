#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// An interface to every <see cref="IMapObject"/> deserialization algorithm.
/// </summary>
struct IMapObjectDeserializer
	: virtual IDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="IMapObjectDeserializer"/> struct.
	/// </summary>
	/// <param name="object_">The object.</param>
	IMapObjectDeserializer(IMapObject& object_)
		: object{ object_ }
	{
	}

	// The deserialized object:
	IMapObject& object;
};

}
