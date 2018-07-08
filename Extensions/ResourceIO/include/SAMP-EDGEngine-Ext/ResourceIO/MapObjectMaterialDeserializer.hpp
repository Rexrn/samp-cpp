#pragma once

#include SAMP_EDGENGINE_EXT_RESOURCEIO_PCH

#include <SAMP-EDGEngine-Ext/ResourceIO/Deserializer.hpp>

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// An interface to every <see cref="IMaterial"/> deserialization algorithm.
/// </summary>
struct IMapObjectMaterialDeserializer
	: virtual IDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="IMapObjectMaterialDeserializer"/> struct.
	/// </summary>
	/// <param name="material_">The deserialized material.</param>
	IMapObjectMaterialDeserializer(IMapObject::IMaterial& material_, Uint8 &materialIndex_)
		:
		material{ material_ },
		materialIndex{ materialIndex_ }
	{
	}

	// The serialized object:
	IMapObject::IMaterial& material;

	Uint8 &materialIndex;
};

}