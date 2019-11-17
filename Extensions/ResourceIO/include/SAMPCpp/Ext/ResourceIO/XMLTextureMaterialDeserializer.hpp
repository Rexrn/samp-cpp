#pragma once
#include SAMPCPP_EXT_RESOURCEIO_PCH

#include "XMLMapObjectMaterialDeserializer.hpp"

namespace samp_cpp::ext::resource_io
{

/// <summary>
/// A XML <see cref="TextureMaterial"/> deserialization algorithm.
/// </summary>
struct XMLTextureMaterialDeserializer
	: XMLMapObjectMaterialDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLTextureMaterialDeserializer" /> struct.
	/// </summary>
	/// <param name="material_">The deserialized material.</param>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="sourceNode_">The source node.</param>
	XMLTextureMaterialDeserializer(IMapObject::IMaterial& material_, Uint8 &materialIndex_, xml::xml_node<> const& sourceNode_)
		:
		XMLMapObjectMaterialDeserializer{ material_, materialIndex_, sourceNode_ }
	{
	}
	
	/// <summary>
	/// Performs deserialization with given setup.
	/// </summary>
	/// <returns>
	///		<c>true</c> if deserialization succeeded; otherwise, <c>false</c>.
	/// </returns>
	virtual bool deserialize() const override;
};

}