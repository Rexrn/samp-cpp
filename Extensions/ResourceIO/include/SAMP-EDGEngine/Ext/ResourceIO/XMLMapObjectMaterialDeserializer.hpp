#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include "XMLDeserializer.hpp"
#include "MapObjectMaterialDeserializer.hpp"

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// An interface for XML material deserialization algorithm.
/// </summary>
struct XMLMapObjectMaterialDeserializer
	:
	IXMLDeserializer,
	IMapObjectMaterialDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLMapObjectMaterialDeserializer" /> struct.
	/// </summary>
	/// <param name="material_">The deserialized material.</param>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="sourceNode_">The source node.</param>
	XMLMapObjectMaterialDeserializer(IMapObject::IMaterial& material_, Uint8 &materialIndex_, xml::xml_node<> const& sourceNode_)
		:
		IXMLDeserializer{ sourceNode_ },
		IMapObjectMaterialDeserializer{ material_, materialIndex_ }
	{
	}

protected:	
	/// <summary>
	/// Deserializes the index of the material.
	/// </summary>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	bool deserializeMaterialIndex() const;
};

}