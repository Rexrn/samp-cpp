#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH



#include "Serializer.hpp"

#include <SAMP-EDGEngine/Everything.hpp>

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// An interface to every <see cref="IMapObject"/> serialization algorithm.
/// </summary>
struct IMapObjectSerializer
	: virtual ISerializer
{	
	/// <summary>
	/// Initializes a new instance of the <see cref="IMapObjectSerializer"/> struct.
	/// </summary>
	/// <param name="object_">The serialized object.</param>
	IMapObjectSerializer(IMapObject const& object_)
		: object{ object_ }
	{
	}

	// The serialized object:
	IMapObject const& object;
};

}