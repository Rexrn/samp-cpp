#pragma once
#include SAMPCPP_EXT_RESOURCEIO_PCH

#include "Serializer.hpp"

namespace samp_cpp::ext::resource_io
{

/// <summary>
/// An interface to every <see cref="IMaterial"/> serialization algorithm.
/// </summary>
struct IMapObjectMaterialSerializer
	: virtual ISerializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="IMapObjectMaterialSerializer"/> struct.
	/// </summary>
	/// <param name="material_">The serialized material.</param>
	IMapObjectMaterialSerializer(IMapObject::IMaterial const& material_, Uint8 materialIndex_)
		:
		material{ material_ },
		materialIndex{ materialIndex_ }
	{
		// # Assertion note:
		// Index of the material cannot be greater than IMapObject::MaxMaterialCount, fix your code.
		assert(materialIndex_ <= IMapObject::MaxMaterialCount);
	}

	// The serialized object:
	IMapObject::IMaterial const& material;

	Uint8 materialIndex;
};

}